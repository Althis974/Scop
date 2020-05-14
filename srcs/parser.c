/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/14 10:48:50 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/14 10:48:50 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

void		file_checker(char **tab, char c)
{
	int len;

	len = get_tab_len((void**)tab);

	if ((c == 'v' && len != 3) || (c == 'f' && (len < 3 && len > 4)))
		error("Wrong file.");
}

GLfloat		*get_vertices(t_env *env, char *line)
{
	int		i;
	char	**tab;
	GLfloat	*new;

	tab = ft_strsplit(&line[1], ' ');

	file_checker(tab, 'v');

	env->obj.v_len += 6;
	new = (GLfloat*)malloc(sizeof(GLfloat) * env->obj.v_len);
	i = -1;
	while (++i < env->obj.v_len - 6)
		new[i] = env->obj.vrtc[i];
	free(env->obj.vrtc);
	env->obj.vrtc = new;
	i = -1;
	while (tab[++i])
	{
		env->obj.vrtc[env->obj.v_len - 6 + i] = (GLfloat)ft_atof(tab[i]);
		env->obj.vrtc[env->obj.v_len - 3 + i] = i * 0.66f;
		ft_strdel(&tab[i]);
	}
	ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
	return (env->obj.vrtc);
}

GLuint		*get_faces(t_env *env, char *line)
{
	int		i;
	int		len;
	char	**tab;
	GLuint	*new;

	tab = ft_strsplit(&line[1], ' ');

	file_checker(tab, 'f');

	len = get_tab_len((void**)tab) == 4 ? 6 : 3;
	env->obj.f_len += len;
	new = (GLuint*)malloc(sizeof(GLuint) * env->obj.f_len);
	i = -1;
	while (++i < env->obj.f_len - len)
		new[i] = env->obj.faces[i];
	free(env->obj.faces);
	env->obj.faces = new;
	i = -1;
	while (++i < 3)
	{
		env->obj.faces[env->obj.f_len - len + i] = (GLuint)ft_atoi(tab[i]) - 1;
		if (len == 6)
			env->obj.faces[env->obj.f_len - len + 3 + i] =
					(GLuint)ft_atoi(tab[i > 0 ? i + 1 : 0]) - 1;
		ft_strdel(&tab[i]);
	}
	ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
	return (env->obj.faces);
}

void		find_sym_axis(t_env *env)
{
	int		i;
	t_vec	max;
	t_vec	min;

	i = 0;
	max = (t_vec){0, 0, 0};
	min = (t_vec){0, 0, 0};
	while (i < env->obj.f_nb - 6)
	{
		env->obj.vrtc[i] > max.x ? max.x = env->obj.vrtc[i] : 0;
		env->obj.vrtc[i] < min.x ? min.x = env->obj.vrtc[i] : 0;
		env->obj.vrtc[i + 1] > max.y ? max.y = env->obj.vrtc[i + 1] : 0;
		env->obj.vrtc[i + 1] < min.y ? min.y = env->obj.vrtc[i + 1] : 0;
		env->obj.vrtc[i + 2] > max.z ? max.z = env->obj.vrtc[i + 2] : 0;
		env->obj.vrtc[i + 2] < min.z ? min.z = env->obj.vrtc[i + 2] : 0;
		i += 6;
	}
	env->obj.sym_axis = ft_vadd(&max, &min);
	env->obj.sym_axis = ft_vmulx(&env->obj.sym_axis, 0.5);
}

void		centralize(t_env *env)
{
	int		i;
	double	o;
	double	tmp;

	i = 0;
	o = 90 * (M_PI / 180);
	while (i < env->obj.v_len)
	{
		env->obj.vrtc[i] -= env->obj.sym_axis.x;
		env->obj.vrtc[i + 1] -= env->obj.sym_axis.y;
		env->obj.vrtc[i + 2] -= env->obj.sym_axis.z;
		tmp = env->obj.vrtc[i] * cos(o) - env->obj.vrtc[i + 2] * sin(o);
		env->obj.vrtc[i + 2] = env->obj.vrtc[i] * sin(o) +
				env->obj.vrtc[i + 2] * cos(o);
		env->obj.vrtc[i] = tmp;
		i += 6;
	}
	env->obj.sym_axis = (t_vec){0, 0, 0};
}

void		parser(t_env *env)
{
	int		fd;
	char	*line;

	if ((fd = open(env->obj.filename, O_RDWR)) == -1)
		error("Open failed.");
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			env->obj.vrtc = get_vertices(env, line);
		else if (line[0] == 'f' && line[1] == ' ')
			env->obj.faces = get_faces(env, line);
		ft_strdel(&line);
	}

	if (!env->obj.vrtc || !env->obj.faces)
		error("Wrong file.");

	ft_strdel(&line);
	env->obj.v_size = env->obj.v_len * sizeof(GLfloat);
	env->obj.f_size = env->obj.f_len * sizeof(GLuint);
	env->obj.f_nb = env->obj.f_len;
	find_sym_axis(env);
	centralize(env);
}