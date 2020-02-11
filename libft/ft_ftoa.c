/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ftoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <rlossy@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 16:22:38 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 16:28:22 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static long		get_len(double nb)
{
	long	size;

	if (nb >= 0.0 && nb <= 1.0)
		return (2);
	if (nb >= -1.0 && nb < 0)
		return (3);
	nb *= 10;
	size = 0;
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb /= 10;
		size++;
	}
	return (++size);
}

char			*ft_ftoa(double nb)
{
	double	n;
	char	*res;
	long	len;

	n = nb;
	nb *= 10;
	len = get_len(n);
	if (!(res = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	res[len + 1] = '\0';
	if (nb < 0)
		nb = -nb;
	res[len] = ((int)nb % 10) + '0';
	nb /= 10;
	res[len - 1] = '.';
	len -= 2;
	while (len >= 0)
	{
		res[len--] = ((int)nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
