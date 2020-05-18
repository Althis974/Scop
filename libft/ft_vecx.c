/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	ft_vaddx(t_vec *v1, double x)
{
	t_vec	v;

	v.x = v1->x + x;
	v.y = v1->y + x;
	v.z = v1->z + x;
	return (v);
}

t_vec	ft_vsubx(t_vec *v1, double x)
{
	t_vec	v;

	v.x = v1->x - x;
	v.y = v1->y - x;
	v.z = v1->z - x;
	return (v);
}

t_vec	ft_vmulx(t_vec *v1, double x)
{
	t_vec	v;

	v.x = v1->x * x;
	v.y = v1->y * x;
	v.z = v1->z * x;
	return (v);
}

t_vec	ft_vdivx(t_vec *v1, double x)
{
	t_vec	v;

	v.x = v1->x / x;
	v.y = v1->y / x;
	v.z = v1->z / x;
	return (v);
}

void	ft_vreg(t_vec *v, double a, double b)
{
	v->x = ft_reg(v->x, a, b);
	v->y = ft_reg(v->y, a, b);
	v->z = ft_reg(v->z, a, b);
}
