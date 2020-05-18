/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void	translate(t_mat *m, t_vec v)
{
	m->m[3] += v.x;
	m->m[7] += v.y;
	m->m[11] += v.z;
}

void	rotate(t_mat *m, t_vec v)
{
	if (v.x)
		*m = mat_rot_axis(*m, AXX, v.x);
	if (v.y)
		*m = mat_rot_axis(*m, AXY, v.y);
	if (v.z)
		*m = mat_rot_axis(*m, AXZ, v.z);
}

void	live_action(t_env *env)
{
	rotate(&env->obj.rotation, convec(0, env->obj.velocity, 0));
	translate(&env->obj.translation, env->obj.inertia);
	camera_move_inertia(env);
	camera_look_at_target(env);
}