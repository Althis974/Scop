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

int			init(t_env *env)
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
	env->shader.vrtx_id = 0;
	env->shader.frag_id = 0;
	env->shader.prgm_id = 0;
	env->event.txt = 0;
	env->event.col = 0;
	env->event.itp = 0;
	return (0);
}

int			main_loop(t_env *env)
{
	glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!events(env))
		return (0);
	set_view(env);
	env->live.model = ft_matmul(&env->obj.trans, &env->obj.rot);
	glUseProgram(env->shader.prgm_id);
	set_mvp(env);
	update_shaders(env);
	glBindTexture(GL_TEXTURE_2D, env->sdl.txt);
	glBindVertexArray(env->sdl.vao);
	glDrawElements(GL_TRIANGLES, env->obj.f_nb, GL_UNSIGNED_INT, 0);
	SDL_GL_SwapWindow(env->sdl.win);
	return (1);
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
		while (1)
		{
			if (!main_loop(&env))
				break ;
		}
		sdl_exit(env.sdl);
	}
	else
		usage();
	return (0);
}
