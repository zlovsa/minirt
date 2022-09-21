/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:27:45 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 15:07:14 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec(float x, float y, float z)
{
	t_vec rv;

	rv.x = x;
	rv.y = y;
	rv.z = z;
	return (rv);
}

t_vec	vsub(t_vec lhs, t_vec rhs)
{
	return (vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z));
}

t_vec	vadd(t_vec lhs, t_vec rhs)
{
	return (vec(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z));
}

t_vec	vmul(t_vec lhs, float k)
{
	return (vec(lhs.x * k, lhs.y * k, lhs.z * k));
}

float	vlen(t_vec v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
