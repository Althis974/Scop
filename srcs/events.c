/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/14 10:48:50 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/14 10:48:50 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

void	move_obj(t_env *env)
{
	t_vec tmp;

	if (env->sdl.evnt.key.keysym.scancode == I)
	{
		tmp = convec(env->cam.front.x, 0, env->cam.front.z);
		tmp = ft_vmulx(&tmp, 0.01);
		env->obj.inertia = ft_vsub(&env->obj.inertia, &tmp);
	}
	if (env->sdl.evnt.key.keysym.scancode == K)
	{
		tmp = convec(env->cam.front.x, 0, env->cam.front.z);
		tmp = ft_vmulx(&tmp, 0.01);
		env->obj.inertia = ft_vadd(&env->obj.inertia, &tmp);
	}
	if (env->sdl.evnt.key.keysym.scancode == J)
	{
		tmp = ft_vmulx(&env->cam.right, 0.01);
		env->obj.inertia = ft_vsub(&env->obj.inertia, &tmp);
	}
	if (env->sdl.evnt.key.keysym.scancode == L)
	{
		tmp = ft_vmulx(&env->cam.right, 0.01);
		env->obj.inertia = ft_vadd(&env->obj.inertia, &tmp);
	}
	if (env->sdl.evnt.key.keysym.scancode == U)
	{
		tmp = ft_vmulx(&env->cam.up, 0.01);
		env->obj.inertia = ft_vadd(&env->obj.inertia, &tmp);
	}
	if (env->sdl.evnt.key.keysym.scancode == O)
	{
		tmp = ft_vmulx(&env->cam.up, 0.01);
		env->obj.inertia = ft_vsub(&env->obj.inertia, &tmp);
	}
}

int		events(t_env *env)
{
	// Event
	SDL_PollEvent(&env->sdl.evnt);
	if (env->sdl.evnt.type == SDL_QUIT || env->sdl.evnt.key.keysym.scancode == ESC)
		return (0);

	env->obj.inertia = ft_vmulx(&env->obj.inertia, INERTIA);
	if (env->sdl.evnt.type == SDL_KEYDOWN)
	{
		if (env->sdl.evnt.key.keysym.scancode == T)
			env->event.txt = env->event.txt > 0 ? 0 : 1;

		move_obj(env);
	}
	live_action(env);

	return (1);
}