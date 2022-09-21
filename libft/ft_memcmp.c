/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:03:51 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:23:20 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			i;
	int				retval;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	retval = 0;
	while (i < n && !retval)
	{
		retval = us1[i] - us2[i];
		i++;
	}
	return (retval);
}
