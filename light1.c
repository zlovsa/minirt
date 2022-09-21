/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:42:27 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/02 18:12:51 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		in_shadow(t_isc isc, t_elem *light, t_scene sc, t_vec *l_dir)
{
	float l_dist;
	t_isc sh_isc;
	t_vec sh_orig;

	*l_dir = vnorm(vsub(light->center, isc.hit));
	l_dist = vlen(vsub(light->center, isc.hit));
	sh_orig = vadd(isc.hit,
				vmul(isc.n, dot(*l_dir, isc.n) < 0 ? -1e-4 : 1e-4));
	return ((scene_intersect(sh_orig, *l_dir, sc, &sh_isc) &&
			vlen(vsub(sh_isc.hit, sh_orig)) < l_dist));
}

void	diff_spec_light(t_scene sc, t_isc isc, t_vec *d_light, t_vec *s_light)
{
	t_vec	l_dir;
	t_elem	*light;

	*s_light = vec(0, 0, 0);
	light = sc.lights;
	while (light)
	{
		if (!in_shadow(isc, light, sc, &l_dir))
		{
			*d_light = vadd(*d_light, vmul(light->mat.color, isc.mat.color_cf
				* light->brightness * maxf(0, dot(l_dir, isc.n))));
			*s_light = vadd(*s_light, vmul(light->mat.color,
				powf(maxf(0, dot(reflect(l_dir, isc.n), isc.dir)),
				isc.mat.spec_exp * light->brightness)));
		}
		light = light->next;
	}
}
