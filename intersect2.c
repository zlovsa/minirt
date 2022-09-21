/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 23:57:34 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 21:19:20 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sp_intersect(t_elem sp, t_vec orig, t_vec dir, t_isc *isc)
{
	float t0;
	t_vec l;
	float tca;
	float d2;
	float thc;

	l = vsub(sp.center, orig);
	tca = dot(l, dir);
	d2 = dot(l, l) - tca * tca;
	if (d2 > sp.radius * sp.radius)
		return (0);
	thc = sqrtf(sp.radius * sp.radius - d2);
	t0 = tca - thc;
	if (t0 < 0)
		t0 = tca + thc;
	if (t0 < 0 || (t0 > isc->obj_dist && isc->obj_dist > -1))
		return (0);
	isc->obj_dist = t0;
	isc->hit = vadd(orig, vmul(dir, t0));
	isc->n = vmul(vnorm(vsub(isc->hit, sp.center)),
			vlen(l) < sp.radius ? -1 : 1);
	isc->mat = sp.mat;
	return (1);
}

int	pl_intersect(t_elem pl, t_vec orig, t_vec dir, t_isc *isc)
{
	float nl;
	float t;

	nl = dot(dir, pl.norm);
	if (fabs(nl) < 1e-6 ||
		(t = dot(vsub(pl.center, orig), pl.norm) / nl) < 0 ||
		(t > isc->obj_dist && isc->obj_dist > -1))
		return (0);
	isc->obj_dist = t;
	isc->hit = vadd(orig, vmul(dir, t));
	isc->n = nl > 0 ? vmul(pl.norm, -1) : pl.norm;
	isc->mat = pl.mat;
	return (1);
}

int	sq_intersect(t_elem sq, t_vec orig, t_vec dir, t_isc *isc)
{
	float nl;
	float t;
	t_vec hit;
	t_vec p;

	nl = dot(dir, sq.norm);
	if (fabs(nl) < 1e-6 ||
		(t = dot(vsub(sq.center, orig), sq.norm) / nl) < 0 ||
		(t > isc->obj_dist && isc->obj_dist > -1))
		return (0);
	hit = vadd(orig, vmul(dir, t));
	p = vsub(hit, sq.center);
	if (fabs(dot(p, sq.vx)) > sq.radius / 2 ||
		fabs(dot(p, sq.vy)) > sq.radius / 2)
		return (0);
	isc->obj_dist = t;
	isc->hit = hit;
	isc->n = nl > 0 ? vmul(sq.norm, -1) : sq.norm;
	isc->mat = sq.mat;
	return (1);
}

int	tr_intersect(t_elem tr, t_vec orig, t_vec dir, t_isc *isc)
{
	float nl;
	float t;
	t_vec hit;

	tr.norm = vnorm(cross(vsub(tr.v1, tr.center), vsub(tr.v2, tr.center)));
	nl = dot(dir, tr.norm);
	if (fabs(nl) < 1e-6 ||
		(t = dot(vsub(tr.center, orig), tr.norm) / nl) < 0 ||
		(t > isc->obj_dist && isc->obj_dist > -1))
		return (0);
	hit = vadd(orig, vmul(dir, t));
	if (dot(tr.norm, cross(vsub(tr.v1, tr.center), vsub(hit, tr.center))) < 0)
		return (0);
	if (dot(tr.norm, cross(vsub(tr.v2, tr.v1), vsub(hit, tr.v1))) < 0)
		return (0);
	if (dot(tr.norm, cross(vsub(tr.center, tr.v2), vsub(hit, tr.v2))) < 0)
		return (0);
	isc->obj_dist = t;
	isc->hit = hit;
	isc->n = nl > 0 ? vmul(tr.norm, -1) : tr.norm;
	isc->mat = tr.mat;
	return (1);
}
