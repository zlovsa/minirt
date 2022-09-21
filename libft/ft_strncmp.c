/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:47:51 by mcarolee          #+#    #+#             */
/*   Updated: 2021/01/29 15:24:02 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(char *s1, char *s2)
{
	int d;

	while (!(d = (unsigned char)*s1 - (unsigned char)*s2) && *s1++ && *s2++)
		;
	return (d);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		d;
	size_t	i;

	i = 0;
	while (!(d = (unsigned char)*s1 - (unsigned char)*s2)
		&& *s1++ && *s2++ && i < n)
		i++;
	return (d);
}
