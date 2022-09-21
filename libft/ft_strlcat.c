/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:23:14 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:31:24 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const char	*s;
	size_t		n;

	n = 0;
	while (*dest)
	{
		dest++;
		n++;
	}
	s = src;
	while ((size_t)(n + s - src + 1) < size && *s)
	{
		*dest = *s;
		dest++;
		s++;
	}
	if (size > 0 && n <= size)
		*dest = 0;
	while (*s)
		s++;
	if (n > size)
		n = size;
	n += s - src;
	return (n);
}
