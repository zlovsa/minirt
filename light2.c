/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:44:42 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 14:49:24 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	reflect(t_vec i, t_vec n)
{
	return (vsub(i, vmul(n, 2 * dot(i, n))));
}

t_vec	refract(t_vec i, t_vec n, float eta_t, float eta_i)
{
	float cosi;
	float eta;
	float k;

	if ((cosi = -maxf(-1, minf(1, dot(i, n)))) < 0)
		return (refract(i, vmul(n, -1), eta_i, eta_t));
	eta = eta_i / eta_t;
	k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? vec(1, 0, 0) :
		vadd(vmul(i, eta), vmul(n, eta * cosi - sqrtf(k))));
}

t_vec	reflect_color(t_scene sc, t_isc isc, int level)
{
	t_vec refl_dir;
	t_vec refl_orig;
	t_vec refl_color;

	refl_dir = reflect(isc.dir, isc.n);
	refl_orig = vadd(isc.hit, vmul(isc.n,
					dot(refl_dir, isc.n) < 0 ? -0.001 : 0.001));
	refl_color = cast_ray(refl_orig, refl_dir, sc, level + 1);
	return (refl_color);
}

t_vec	refract_color(t_scene sc, t_isc isc, int level)
{
	t_vec refr_dir;
	t_vec refr_color;
	t_vec refr_orig;

	refr_dir = vnorm(refract(isc.dir, isc.n, isc.mat.refr_idx, 1));
	refr_orig = vadd(isc.hit, vmul(isc.n,
					dot(refr_dir, isc.n) < 0 ? -0.001 : 0.001));
	refr_color = cast_ray(refr_orig, refr_dir, sc, level + 1);
	return (refr_color);
}
