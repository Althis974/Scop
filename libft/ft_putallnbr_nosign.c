/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putallnbr_nosign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putallnbr_nosign(intmax_t n)
{
	if (n == INT64_MIN)
	{
		ft_putchar('9');
		ft_putallnbr(223372036854775808);
	}
	else
	{
		if (n < 0)
			if (n != INT64_MIN)
				n *= -1;
		if (n < 10)
			ft_putchar(n + '0');
		if (n > 9)
		{
			ft_putallnbr(n / 10);
			ft_putchar(n % 10 + '0');
		}
	}
}
