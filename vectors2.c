/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:30:01 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/02 18:13:40 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot(t_vec lhs, t_vec rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

t_vec	cross(t_vec a, t_vec b)
{
	return (vec(a.y * b.z - a.z * b.y,
				b.x * a.z - b.z * a.x,
				a.x * b.y - b.x * a.y));
}

t_vec	vnorm(t_vec l)
{
	return (vmul(l, 1. / sqrt(dot(l, l))));
}

t_vec	color_mul(t_vec a, t_vec b)
{
	return (vec(a.x * b.x, a.y * b.y, a.z * b.z));
}
