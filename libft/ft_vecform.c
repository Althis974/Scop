/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecform.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ft_vnorm(t_vec *v)
{
	double	n;

	n = 1.0 / sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	v->x *= n;
	v->y *= n;
	v->z *= n;
}

double	ft_vdot(t_vec *v1, t_vec *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

double	ft_vlen(t_vec *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

double	ft_vdist(t_vec *v1, t_vec *v2)
{
	double	dist;

	dist = sqrt((v1->x - v2->x) * (v1->x - v2->x) + \
	(v1->y - v2->y) * (v1->y - v2->y) + (v1->z - v2->z) * (v1->z - v2->z));
	return (dist);
}

t_vec	ft_vreflect(t_vec *intensity, t_vec *normal)
{
	t_vec	v;

	v.x = intensity->x - 2.0 * ft_vdot(normal, intensity) * normal->x;
	v.y = intensity->y - 2.0 * ft_vdot(normal, intensity) * normal->y;
	v.z = intensity->z - 2.0 * ft_vdot(normal, intensity) * normal->z;
	return (v);
}
