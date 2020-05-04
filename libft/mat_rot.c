/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mat_rot.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 15:42:51 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 15:42:51 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	get_axx_mat_rot(t_mat *m, double theta)
{
	m->m[5] = cos(theta);
	m->m[6] = sin(theta);
	m->m[9] = -sin(theta);
	m->m[10] = cos(theta);
}

void	get_axy_mat_rot(t_mat *m, double theta)
{
	m->m[0] = cos(theta);
	m->m[2] = -sin(theta);
	m->m[8] = sin(theta);
	m->m[10] = cos(theta);
}

void	get_axz_mat_rot(t_mat *m, double theta)
{
	m->m[0] = cos(theta);
	m->m[1] = sin(theta);
	m->m[4] = -sin(theta);
	m->m[5] = cos(theta);
}

t_mat	mat_rot_axis(t_mat m, int axis, double angle)
{
	t_mat	rot;
	double	theta;

	mat4_set(&rot, ID);
	theta = angle * (M_PI / 180);
	if (axis == AXX)
	{
		get_axx_mat_rot(&rot, theta);
		m = ft_matmul(&m, &rot);
	}
	else if (axis == AXY)
	{
		get_axy_mat_rot(&rot, theta);
		m = ft_matmul(&m, &rot);
	}
	else if (axis == AXZ)
	{
		get_axz_mat_rot(&rot, theta);
		m = ft_matmul(&m, &rot);
	}

	return (m);
}

