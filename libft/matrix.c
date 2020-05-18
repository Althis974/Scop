/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	set_matid(t_mat *m, int order)
{
	int i;
	int j;

	i = -1;
	while (++i < order)
	{
		j = -1;
		while (++j < order)
			m->m[i][j] = j % order == 0 ? 1 : 0;
	}
}*/

void	set_mat(t_mat *m, float f)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (f == 0x6964)
			m->m[i] = (i % 5 == 0 ? 1 : 0);
		else
			m->m[i] = f;
	}
}

/*
t_mat	ft_matmul(t_mat *a, t_mat *b)
{
	int		h;
	int		w;
	int		z;
	t_mat	m;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
		{
			m.m[h][w] = 0;
			z = -1;
			while (++z < 4)
				m.m[h][w] += a->m[h][z] * b->m[z][w];
		}
	}
	return (m);
}*/

t_mat	ft_matmul(t_mat *a, t_mat *b)
{
	int		h;
	int		w;
	int		z;
	t_mat	m;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
		{
			z = -1;
			m.m[h * 4 + w] = 0;
			while (++z < 4)
				m.m[h * 4 + w] += a->m[h * 4 + z] * b->m[z * 4 + w];
		}
	}
	return (m);
}
/*
t_mat	ft_matranspose(t_mat *m)
{
	int		h;
	int		w;
	t_mat	t;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
			t.m[w][h] = m->m[h][w];
	}
	return (t);
}*/

t_mat	ft_matranspose(t_mat *m)
{
	int		h;
	int		w;
	t_mat	t;

	h = -1;
	while (++h < 4)
	{
		w = -1;
		while (++w < 4)
			t.m[w * 4 + h] = m->m[h * 4 + w];
	}
	return (t);
}