/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:03:51 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/08 19:30:03 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *rv;
	long l;

	l = ft_strlen(s);
	if ((rv = (char *)malloc((l + 1) * sizeof(char))))
		ft_memcpy(rv, s, l + 1);
	return (rv);
}
