/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/20 10:51:27 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_mat(t_mat *a, float f)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (f == ID)
			a->m[i] = (i % 5 == 0 ? 1 : 0);
		else
			a->m[i] = f;
	}
}

t_mat	ft_matmul(t_mat *a, t_mat *b)
{
	int		i;
	int		j;
	int		k;
	t_mat	m;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			m.m[i * 4 + j] = 0;
			while (++k < 4)
				m.m[i * 4 + j] += a->m[i * 4 + k] * b->m[k * 4 + j];
		}
	}
	return (m);
}

t_mat	ft_matranspose(t_mat *a)
{
	int		i;
	int		j;
	t_mat	m;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			m.m[j * 4 + i] = a->m[i * 4 + j];
	}
	return (m);
}
