/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   live.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/14 10:48:50 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/14 10:48:50 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
		*m = mat_rot_axis(*m, AXIS_X, v.x);
	if (v.y)
		*m = mat_rot_axis(*m, AXIS_Y, v.y);
	if (v.z)
		*m = mat_rot_axis(*m, AXIS_Z, v.z);
}

void	live_action(t_env *env, double inertia)
{
	rotate(&env->obj.rotation, convec(0, env->obj.velocity, 0));
	env->obj.inertia = ft_vmulx(&env->obj.inertia, inertia);
	translate(&env->obj.translation, env->obj.inertia);

	camera_move_inertia(env, 0.93);
	camera_look_at_target(env);
}