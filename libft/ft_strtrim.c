/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlossy <rlossy@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 10:08:13 by rlossy            #+#    #+#             */
/*   Updated: 2020/05/18 10:08:13 by rlossy           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;

	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	start = 0;
	while (s[start] == '\t' || s[start] == '\n' || s[start] == ' ')
		start++;
	if (s[start] == '\0')
		return (ft_strdup(s + start));
	while ((s[len] == '\t' || s[len] == '\n' || s[len] == ' ') && len > 0)
		len--;
	return (ft_strsub(s, start, (len - start + 1)));
}
