/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec	ft_vadd(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->x + v2->x;
	v.y = v1->y + v2->y;
	v.z = v1->z + v2->z;
	return (v);
}

t_vec	ft_vsub(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->x - v2->x;
	v.y = v1->y - v2->y;
	v.z = v1->z - v2->z;
	return (v);
}

t_vec	ft_vmul(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->x * v2->x;
	v.y = v1->y * v2->y;
	v.z = v1->z * v2->z;
	return (v);
}

t_vec	ft_vdiv(t_vec *v1, t_vec *v2)
{
	t_vec	v;

	v.x = v1->x / v2->x;
	v.y = v1->y / v2->y;
	v.z = v1->z / v2->z;
	return (v);
}

t_vec	ft_vcross(t_vec *v1, t_vec *v2)
{
	t_vec v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v1->z * v2->x - v1->x * v2->z;
	v.z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}
