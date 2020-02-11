/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlossy <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 09:21:33 by rlossy       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/14 15:22:18 by rlossy      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char *s1, char *s2, int type)
{
	if (type == 1)
		free(s1);
	else if (type == 2)
		free(s2);
	else if (type == 3)
	{
		free(s1);
		free(s2);
	}
}

char		*ft_strjoin(char *s1, char *s2, int free)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if ((str = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	ft_free(s1, s2, free);
	return (str);
}
