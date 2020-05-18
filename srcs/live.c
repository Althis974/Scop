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

void	set_projection(t_env *env)
{
	float	s;
	float	far;
	float	near;

	far = 100.0;
	near = 0.001;
	s = 1 / (tan(FOV * 0.5 * M_PI / 180.0));
	set_mat(&env->live.projection, 0),
			env->live.projection.m[0] = s / ((float)WIN_W / (float)WIN_H);
	env->live.projection.m[5] = s;
	env->live.projection.m[10] = -(far + near) / (far - near);
	env->live.projection.m[11] = -1;
	env->live.projection.m[14] = -2 * far * near / (far - near);
}

void	set_mvp(t_env *env)
{
	t_mat tmp;
	t_mat trans;

	tmp = ft_matmul(&env->live.view, &env->live.projection);
	trans = ft_matranspose(&env->live.model);
	env->live.mvp = ft_matmul(&trans, &tmp);
}

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
	rotate(&env->obj.rot, convec(0, env->obj.velo, 0));
	translate(&env->obj.trans, env->obj.iner);
	camera_tracking(env);
	set_view(env);
}