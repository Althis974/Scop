/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_print_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ft_get_print_len(uintmax_t n, uintmax_t base, size_t *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (*len == 0)
		*len += 1;
	if (n >= base)
	{
		*len += 1;
		ft_get_print_len(n / base, base, len);
	}
}
