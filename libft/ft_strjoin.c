/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:36:00 by mcarolee          #+#    #+#             */
/*   Updated: 2021/01/29 15:14:55 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char *r;
	char *t;

	if (!(r = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (r);
	t = r;
	while (s1 && *s1)
		*t++ = *s1++;
	while (s2 && *s2)
		*t++ = *s2++;
	*t = 0;
	return (r);
}
