/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	move_obj(t_env *env)
{
	t_vec tmp;

	tmp = ft_vmulx(&env->cam.lgtnal, 0.01);
	if (env->sdl.evnt.key.keysym.scancode == I)
		env->obj.iner = ft_vadd(&env->obj.iner, &tmp);
	if (env->sdl.evnt.key.keysym.scancode == K)
		env->obj.iner = ft_vsub(&env->obj.iner, &tmp);
	tmp = ft_vmulx(&env->cam.trvsal, 0.01);
	if (env->sdl.evnt.key.keysym.scancode == J)
		env->obj.iner = ft_vsub(&env->obj.iner, &tmp);
	if (env->sdl.evnt.key.keysym.scancode == L)
		env->obj.iner = ft_vadd(&env->obj.iner, &tmp);
	tmp = convec(env->cam.sgttal.x, 0, env->cam.sgttal.z);
	tmp = ft_vmulx(&tmp, 0.01);
	if (env->sdl.evnt.key.keysym.scancode == U)
		env->obj.iner = ft_vsub(&env->obj.iner, &tmp);
	if (env->sdl.evnt.key.keysym.scancode == O)
		env->obj.iner = ft_vadd(&env->obj.iner, &tmp);
}

void	move_cam(t_env *env)
{
	t_vec tmp;

	tmp = ft_vmulx(&env->cam.lgtnal, env->cam.velo);
	if (env->sdl.evnt.key.keysym.scancode == Z)
		env->cam.iner = ft_vadd(&env->cam.iner, &tmp);
	if (env->sdl.evnt.key.keysym.scancode == S)
		env->cam.iner = ft_vsub(&env->cam.iner, &tmp);
	tmp = ft_vmulx(&env->cam.trvsal, env->cam.velo);
	if (env->sdl.evnt.key.keysym.scancode == Q)
		env->cam.iner = ft_vsub(&env->cam.iner, &tmp);
	if (env->sdl.evnt.key.keysym.scancode == D)
		env->cam.iner = ft_vadd(&env->cam.iner, &tmp);
	tmp = ft_vmulx(&env->cam.sgttal, env->cam.velo);
	if (env->sdl.evnt.key.keysym.scancode == A)
		env->cam.iner = ft_vsub(&env->cam.iner, &tmp);
	if (env->sdl.evnt.key.keysym.scancode == E)
		env->cam.iner = ft_vadd(&env->cam.iner, &tmp);
}

void	apply_texture(t_env *env)
{
	if (env->obj.txt.img)
		ft_strdel(&env->obj.txt.img);
	env->event.txt = env->event.txt == 4 ? 0 : env->event.txt + 1;
	if (env->event.txt == 1)
		load_texture(env, "./textures/kitten.bmp");
	else if (env->event.txt == 2)
		load_texture(env, "./textures/fire.bmp");
	else if (env->event.txt == 3)
		load_texture(env, "./textures/water.bmp");
	else if (env->event.txt == 4)
		load_texture(env, "./textures/grass.bmp");
	opengl_set_texture(env);
}

int		events(t_env *env)
{
	SDL_PollEvent(&env->sdl.evnt);
	if (env->sdl.evnt.type == SDL_QUIT
		|| env->sdl.evnt.key.keysym.scancode == ESC)
		return (0);
	env->obj.iner = ft_vmulx(&env->obj.iner, INERTIA);
	env->cam.iner = ft_vmulx(&env->cam.iner, INERTIA);
	if (env->sdl.evnt.type == SDL_KEYDOWN)
	{
		if (env->sdl.evnt.key.keysym.scancode == T)
			apply_texture(env);
		if (env->sdl.evnt.key.keysym.scancode == C)
			env->event.col = env->event.col > 0 ? 0 : 1;
		if (env->sdl.evnt.key.keysym.scancode == N)
			env->event.itp = env->event.itp > 0 ? 0 : 1;
		move_obj(env);
		move_cam(env);
	}
	live_action(env);
	return (1);
}
