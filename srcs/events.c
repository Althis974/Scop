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

int		events(t_env *env)
{
	// Event
	SDL_PollEvent(&env->sdl.evnt);
	if (env->sdl.evnt.type == SDL_QUIT || env->sdl.evnt.key.keysym.scancode == ESC)
		return (0);

	if (env->sdl.evnt.type == SDL_KEYDOWN)
	{
		if (env->sdl.evnt.key.keysym.scancode == T)
			env->event.txt = env->event.txt > 0 ? 0 : 1;
	}

	return (1);
}