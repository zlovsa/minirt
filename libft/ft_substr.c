/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:36:00 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:33:34 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	size_t	i;
	char	*r;

	if (!s)
		return (NULL);
	l = 0;
	while (s[l])
		l++;
	if (start >= l)
		len = 0;
	else if (start + len > l)
		len = l - start;
	if ((r = (char*)malloc(len + 1)))
	{
		i = 0;
		while (i < len)
		{
			r[i] = s[start + i];
			i++;
		}
		r[len] = 0;
	}
	return (r);
}
