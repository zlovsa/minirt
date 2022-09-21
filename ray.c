/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:12:41 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/02 18:52:21 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		scene_intersect(t_vec orig, t_vec dir, t_scene sc, t_isc *isc)
{
	t_elem *obj;

	obj = sc.objs;
	isc->obj_dist = -1;
	isc->orig = orig;
	isc->dir = dir;
	while (obj)
	{
		if (!ft_strcmp(obj->typeid, "sp"))
			sp_intersect(*obj, orig, dir, isc);
		else if (!ft_strcmp(obj->typeid, "pl"))
			pl_intersect(*obj, orig, dir, isc);
		else if (!ft_strcmp(obj->typeid, "sq"))
			sq_intersect(*obj, orig, dir, isc);
		else if (!ft_strcmp(obj->typeid, "cy"))
			cy_intersect(*obj, orig, dir, isc);
		else if (!ft_strcmp(obj->typeid, "tr"))
			tr_intersect(*obj, orig, dir, isc);
		obj = obj->next;
	}
	return (isc->obj_dist > -1);
}

t_vec	cast_ray(t_vec orig, t_vec dir, t_scene sc, int level)
{
	t_isc isc;
	t_vec d_light;
	t_vec s_light;
	t_vec refl_color;
	t_vec refr_color;

	if (level > 6 || !scene_intersect(orig, dir, sc, &isc))
		return (vec(0, 0, 0));
	d_light = vmul(sc.ambient->mat.color, sc.ambient->brightness);
	refl_color = reflect_color(sc, isc, level);
	refr_color = refract_color(sc, isc, level);
	diff_spec_light(sc, isc, &d_light, &s_light);
	return (vadd(color_mul(isc.mat.color, vadd(d_light, s_light)),
				vadd(vmul(refl_color, isc.mat.refl_cf),
					vmul(refr_color, isc.mat.refr_cf))));
}

t_vec	get_dir(t_scene *sc, t_elem *cam, int i, int j)
{
	float x;
	float y;

	x = (2 * (i + 0.5) / (float)sc->res->resx - 1) * cam->tgx;
	y = (2 * (j + 0.5) / (float)sc->res->resy - 1) * cam->tgy;
	return (vnorm(vadd(cam->norm, vadd(vmul(cam->vx, x), vmul(cam->vy, -y)))));
}

void	render(t_scene *sc, t_elem *cam)
{
	int j;
	int i;

	cam->tgx = tan(cam->fov * 3.141592653589793 / 360.);
	cam->tgy = cam->tgx * sc->res->resy / (float)sc->res->resx;
	j = -1;
	sc->img = (t_vec *)malloc(sizeof(t_vec) * sc->res->resx * sc->res->resy);
	if (!sc->img)
		return ;
	while (++j < sc->res->resy && (i = -1))
		while (++i < sc->res->resx)
			sc->img[j * sc->res->resx + i] =
				cast_ray(cam->center, get_dir(sc, cam, i, j), *sc, 0);
}
