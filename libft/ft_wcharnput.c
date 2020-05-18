/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharnput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

size_t		ft_wcharnput(wchar_t const *s, size_t len, int print)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	j = 0;
	res = 0;
	while (s[j] && i <= len)
	{
		if ((i += ft_wcharlen(s[j])) > len)
			break ;
		j++;
	}
	if (print == 1)
		ft_putnwstr(s, j);
	i = 0;
	while (i < j)
	{
		res += ft_wcharlen(s[i]);
		i++;
	}
	return (res);
}
