/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vcpy(t_vec *v1, t_vec *v2)
{
	v1->x = v2->x;
	v1->y = v2->y;
	v1->z = v2->z;
}

t_vec	convec(double x, double y, double z)
{
	t_vec v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}