/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:59:25 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/08 19:30:10 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	if (!dest || !src)
		return (dest);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}
