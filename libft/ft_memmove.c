/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:59:25 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:25:46 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	if (!dest || !src)
		return (dest);
	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	i = (s <= d && d <= s + n) ? n : 0;
	if (s <= d && d <= s + n)
		while (i)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	else
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	return (dest);
}
