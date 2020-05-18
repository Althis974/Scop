/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int		ft_putnwstr(wchar_t const *s, size_t len)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (i < len)
		{
			ft_putwchar(s[i]);
			i++;
		}
	}
	return (i);
}
