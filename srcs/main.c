/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 11:58:09 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		usage()
{
	write(2, "usage : ./scop <filename>\n", 26);
}

void		error(const char *err)
{
	write(2, "Error: ", 7);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	exit(1);
}

int 		init(t_env *env)
{
	if (sdl_init(env))
		return (-1);
	set_cam(env);
	set_projection(env);
	set_mat(&env->live.model, ID);
	set_mat(&env->live.view, ID);
	set_mat(&env->obj.rot, ID);
	set_mat(&env->obj.trans, ID);
	env->obj.f_len = 0;
	env->obj.v_len = 0;
	env->obj.iner = (t_vec){0, 0, 0};
	env->obj.sym_ax = (t_vec){0, 0, 0};
	env->obj.velo = 0.33;
	env->shader.vrtxID = 0;
	env->shader.fragID = 0;
	env->shader.prgmID = 0;
	env->event.txt = 0;
	env->event.col = 0;
	env->event.itp = 0;
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;

	if (ac == 2 && !(ft_strcmp(&av[1][ft_strlen(av[1]) - 4], ".obj")))
	{
		env.obj.filename = av[1];
		init(&env);
		parser(&env);
		load_shader(&env);
		opengl_set_buffers(&env);
		//glBindVertexArray(0);
		//glEnable(GL_DEPTH_TEST);
		while (1)
		{
			glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (!events(&env))
				break;

			set_view(&env);

			env.live.model = ft_matmul(&env.obj.trans, &env.obj.rot);

			glUseProgram(env.shader.prgmID);

			set_mvp(&env);

			update_shaders(&env);

			glBindTexture(GL_TEXTURE_2D, env.sdl.txt);

			glBindVertexArray(env.sdl.vao);
			glDrawElements(GL_TRIANGLES, env.obj.f_nb, GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0);
			SDL_GL_SwapWindow(env.sdl.win);
		}
		sdl_exit(env.sdl);
	}
	else
		usage();

	return (0);
}