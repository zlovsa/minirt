/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:01:20 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:32:11 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	l;
	char	*r;

	if (!s || !f)
		return (NULL);
	l = 0;
	while (s[l])
		l++;
	if ((r = (char*)malloc(l + 1)))
	{
		i = 0;
		while (i < l)
		{
			r[i] = (*f)(i, s[i]);
			i++;
		}
		r[i] = 0;
	}
	return (r);
}
