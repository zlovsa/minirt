/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:23:14 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:31:53 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*s;
	size_t		n;

	s = src;
	n = size;
	if (s && dest)
	{
		if (n)
		{
			n--;
			while (n && *s)
			{
				*dest = *s;
				dest++;
				s++;
				n--;
			}
			*dest = 0;
		}
		while (*s)
			s++;
	}
	return (s - src);
}
