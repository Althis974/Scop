/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/14 10:48:50 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/14 10:48:50 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

void		set_cam(t_env *env)
{
	t_vec	v1;

	v1 = (t_vec){0, 1, 0};
	env->cam.ori = (t_vec){0, 0, 3};
	env->cam.target = (t_vec){0, 0, 0};
	env->cam.dir = ft_vsub(&env->cam.ori, &env->cam.target);
	ft_vnorm(&env->cam.dir);
	env->cam.right = ft_vcross(&v1, &env->cam.dir);
	ft_vnorm(&env->cam.right);
	env->cam.up = ft_vcross(&env->cam.dir, &env->cam.right);
	env->cam.front = ft_vcross(&env->cam.up, &env->cam.right);
	env->cam.inertia = (t_vec){0, 0, 0};
	env->cam.velocity = 0.005;
}

void		error(const char *err)
{
	write(2, "Error: ", 7);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	exit(1);
}

void		usage()
{
	write(2, "usage : ./scop <filename>\n", 26);
}

int 		init(t_env *env)
{
	if (SDLInit(env))
		return (-1);
	set_cam(env);
	set_mat(&env->live.model, ID);
	set_mat(&env->live.view, ID);
	set_projection_matrix(env, FOV);
	set_mat(&env->obj.rotation, ID);
	set_mat(&env->obj.translation, ID);
	env->obj.f_len = 0;
	env->obj.v_len = 0;
	env->obj.inertia = (t_vec){0, 0, 0};
	env->obj.sym_axis = (t_vec){0, 0, 0};
	env->obj.velocity = 0.33;
	env->event.txt = 0;
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
		load_bmp(&env, "./resources/chaton.bmp");
		build_shader_program(&env);
		create_buffers(&env);
		//glBindVertexArray(0);
		//glEnable(GL_DEPTH_TEST);
		while (1)
		{
			glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (!events(&env))
				break;

			//live_action(&env);

			camera_look_at_target(&env);

			env.live.model = ft_matmul(&env.obj.translation, &env.obj.rotation);

			glUseProgram(env.shader.program);

			compute_mvp_matrix(&env);

			update_shader_uniforms(&env);

			glBindTexture(GL_TEXTURE_2D, env.sdl.txt);

			glBindVertexArray(env.sdl.vao);
			glDrawElements(GL_TRIANGLES, env.obj.f_nb, GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0);
			SDL_GL_SwapWindow(env.sdl.win);
		}
		SDLExit(env.sdl);
	}
	else
		usage();

	return (0);
}