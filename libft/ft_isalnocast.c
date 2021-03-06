/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnocast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnocast(int c)
{
	if (c == '%' || (c >= 65 && c <= 90) || (c >= 97 && c <= 103) || c == 105
			|| c == 107 || (c >= 109 && c <= 121))
		return (1);
	return (0);
}
