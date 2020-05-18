/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
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

void	camera_look_at_target(t_env *env)
{
	t_vec	tmp;
	t_mat	view;

	tmp = env->cam.up;
	env->cam.front = ft_vsub(&env->cam.ori, &env->cam.target);
	ft_vnorm(&env->cam.front);
	env->cam.right = ft_vcross(&env->cam.up, &env->cam.front);
	ft_vnorm(&env->cam.right);
	tmp = ft_vcross(&env->cam.front, &env->cam.right);
	set_mat(&view, ID);
	view.m[0] = (float)env->cam.right.x;
	view.m[1] = (float)tmp.x;
	view.m[2] = (float)env->cam.front.x;
	view.m[4] = (float)env->cam.right.y;
	view.m[5] = (float)tmp.y;
	view.m[6] = (float)env->cam.front.y;
	view.m[8] = (float)env->cam.right.z;
	view.m[9] = (float)tmp.z;
	view.m[10] = (float)env->cam.front.z;
	view.m[12] = (float)-ft_vdot(&env->cam.right, &env->cam.ori);
	view.m[13] = (float)-ft_vdot(&tmp, &env->cam.ori);
	view.m[14] = (float)-ft_vdot(&env->cam.front, &env->cam.ori);
	env->live.view = view;
}

void	compute_mvp_matrix(t_env *env)
{
	t_mat tmp;
	t_mat trans;

	tmp = ft_matmul(&env->live.view, &env->live.projection);
	trans = ft_matranspose(&env->live.model);
	env->live.mvp = ft_matmul(&trans, &tmp);
}

void	set_projection_matrix(t_env *env, float fov)
{
	float	s;
	float	far;
	float	near;

	far = 100.0;
	near = 0.001;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	set_mat(&env->live.projection, 0),
	env->live.projection.m[0] = s / ((float)WIN_W / (float)WIN_H);
	env->live.projection.m[5] = s;
	env->live.projection.m[10] = -(far + near) / (far - near);
	env->live.projection.m[11] = -1;
	env->live.projection.m[14] = -2 * far * near / (far - near);
}

void	camera_move_inertia(t_env *env)
{
	t_vec	old;
	t_vec	tmp;

	vcpy(&old, &env->cam.ori);

	env->cam.ori = ft_vadd(&env->cam.ori, &env->cam.inertia);

	tmp = ft_vsub(&env->cam.ori, &old);
	env->cam.target = ft_vadd(&env->cam.target, &tmp);
}