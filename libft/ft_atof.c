/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *s)
{
	int		exp;
	int		sign;
	double	i;
	double	val;

	i = 1;
	val = 0;
	sign = 0;
	while (ft_isblank(*s))
		s++;
	*s == '-' ? sign = 1 : 0;
	*s == '-' || *s == '+' ? s++ : 0;
	while ('0' <= *s && *s <= '9')
		val = val * 10 + (*s++ - '0');
	if (*s == '.' && (s++))
		while ('0' <= *s && *s <= '9')
			val += (*s++ - '0') / (i *= 10);
	if (*s == 'E' && (s++))
	{
		exp = ft_atoi(s);
		if (exp)
			val = val * ft_pow(10, exp);
	}
	return (sign && val > 0 ? -val : val);
}