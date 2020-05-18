/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 11:58:09 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

void		set_cam(t_env *env)
{
	t_vec	tmp;

	tmp = (t_vec){0, 1, 0};
	env->cam.ori = (t_vec){0, 0, 3};
	env->cam.tgt = (t_vec){0, 0, 0};
	env->cam.dir = ft_vsub(&env->cam.ori, &env->cam.tgt);
	ft_vnorm(&env->cam.dir);
	env->cam.trvsal = ft_vcross(&tmp, &env->cam.dir);
	ft_vnorm(&env->cam.trvsal);
	env->cam.lgtnal = ft_vcross(&env->cam.dir, &env->cam.trvsal);
	env->cam.sgttal = ft_vcross(&env->cam.lgtnal, &env->cam.trvsal);
	env->cam.iner = (t_vec){0, 0, 0};
	env->cam.velo = 0.005;
}

void		set_view(t_env *env)
{
	t_vec	tmp;
	t_mat	view;

	tmp = env->cam.lgtnal;
	env->cam.sgttal = ft_vsub(&env->cam.ori, &env->cam.tgt);
	ft_vnorm(&env->cam.sgttal);
	env->cam.trvsal = ft_vcross(&env->cam.lgtnal, &env->cam.sgttal);
	ft_vnorm(&env->cam.trvsal);
	tmp = ft_vcross(&env->cam.sgttal, &env->cam.trvsal);
	set_mat(&view, ID);
	view.m[0] = (float)env->cam.trvsal.x;
	view.m[1] = (float)tmp.x;
	view.m[2] = (float)env->cam.sgttal.x;
	view.m[4] = (float)env->cam.trvsal.y;
	view.m[5] = (float)tmp.y;
	view.m[6] = (float)env->cam.sgttal.y;
	view.m[8] = (float)env->cam.trvsal.z;
	view.m[9] = (float)tmp.z;
	view.m[10] = (float)env->cam.sgttal.z;
	view.m[12] = (float)-ft_vdot(&env->cam.trvsal, &env->cam.ori);
	view.m[13] = (float)-ft_vdot(&tmp, &env->cam.ori);
	view.m[14] = (float)-ft_vdot(&env->cam.sgttal, &env->cam.ori);
	env->live.view = view;
}

void		camera_tracking(t_env *env)
{
	t_vec	old;
	t_vec	tmp;

	vcpy(&old, &env->cam.ori);
	env->cam.ori = ft_vadd(&env->cam.ori, &env->cam.iner);
	tmp = ft_vsub(&env->cam.ori, &old);
	env->cam.tgt = ft_vadd(&env->cam.tgt, &tmp);
}