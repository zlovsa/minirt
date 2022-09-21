/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:59:25 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/08 19:30:21 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char*)src;
	d = (unsigned char*)dest;
	while (n--)
		if ((*d++ = *s++) == (unsigned char)c)
			return (d);
	return (NULL);
}
