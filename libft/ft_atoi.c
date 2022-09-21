/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:47:51 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:46:04 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char *str)
{
	long long retval;
	long long sign;

	retval = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '+' || *str == '-') ? 1 : 0;
	while ('0' <= *str && *str <= '9')
		retval = retval * 10 + sign * (*str++ - '0');
	return ((int)retval);
}
