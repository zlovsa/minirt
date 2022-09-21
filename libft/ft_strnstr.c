/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:47:51 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/08 00:42:07 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	j = 0;
	while (*big && j < len)
	{
		i = 0;
		while (big[i] == little[i] && big[i] && little[i] && j + i < len)
			i++;
		if (!little[i])
			return ((char *)big);
		big++;
		j++;
	}
	return (NULL);
}
