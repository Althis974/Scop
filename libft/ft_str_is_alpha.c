/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_is_alpha.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 09:19:03 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/02 14:34:46 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_alpha(const char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (ft_isalpha(s[i]) == 0)
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
