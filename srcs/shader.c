/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void			create_program(t_env *env)
{
	GLint	link_err;

	env->shader.prgm_id = glCreateProgram();
	glAttachShader(env->shader.prgm_id, env->shader.vrtx_id);
	glAttachShader(env->shader.prgm_id, env->shader.frag_id);
	glLinkProgram(env->shader.prgm_id);
	glGetProgramiv(env->shader.prgm_id, GL_LINK_STATUS, &link_err);
	if (!link_err)
		error("Failed to link program.");
	glDeleteShader(env->shader.vrtx_id);
	glDeleteShader(env->shader.frag_id);
}

const GLchar	*get_shader(char *filename)
{
	int		fd;
	int		ret;
	char	*src;
	char	*tmp;
	char	buff[BUFF_SIZE];

	src = ft_strnew(BUFF_SIZE);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error("Failed to open shader file.");
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		tmp = src;
		src = ft_strjoin(src, buff, 0);
		ft_strdel(&tmp);
	}
	close(fd);
	return (src);
}

GLuint			compile_shader(char *filename, int type)
{
	GLint			compile_err;
	GLuint			shader;
	const GLchar	*src_shader;

	src_shader = get_shader(filename);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &src_shader, NULL);
	glCompileShader(shader);
	free((void*)src_shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_err);
	if (!compile_err)
		error("Failed to compile shader.");
	return (shader);
}

void			load_shader(t_env *env)
{
	env->shader.vrtx_id = compile_shader("./Shaders/vertex.glsl",
			GL_VERTEX_SHADER);
	env->shader.frag_id = compile_shader("./Shaders/fragment.glsl",
			GL_FRAGMENT_SHADER);
	create_program(env);
	env->shader.mvploc = glGetUniformLocation(env->shader.prgm_id, "mvp");
	env->shader.txtloc = glGetUniformLocation(env->shader.prgm_id, "txt");
	env->shader.apploc = glGetUniformLocation(env->shader.prgm_id, "apply");
	env->shader.colloc = glGetUniformLocation(env->shader.prgm_id, "color");
	env->shader.itploc = glGetUniformLocation(env->shader.prgm_id, "inter");
}

void			update_shaders(t_env *env)
{
	glUniformMatrix4fv(env->shader.mvploc, 1, GL_FALSE, env->live.mvp.m);
	//glUniform1i(env->shader.txtloc, env->event.txt);
	glUniform1i(env->shader.apploc, env->event.txt);
	glUniform1i(env->shader.colloc, env->event.col);
	glUniform1i(env->shader.itploc, env->event.itp);
}
