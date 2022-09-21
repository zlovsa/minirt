/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:32:58 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 14:57:05 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quad_eq_solve(float a, float b, float c, float *t)
{
	float d;

	if ((d = b * b - 4 * a * c) < 0)
		return (0);
	t[0] = (-b - sqrtf(d)) / (2 * a);
	t[1] = (-b + sqrtf(d)) / (2 * a);
	return (1);
}

int	cy_solve(t_elem cy, t_vec orig, t_vec dir, float *t)
{
	t_vec av;
	t_vec ap;
	t_vec dp;
	float nl;

	av = vsub(dir, vmul(cy.norm, dot(dir, cy.norm)));
	dp = vsub(orig, cy.center);
	ap = vsub(dp, vmul(cy.norm, dot(dp, cy.norm)));
	if (!quad_eq_solve(dot(av, av), 2 * dot(av, ap),
					dot(ap, ap) - cy.radius * cy.radius, t))
		return (0);
	nl = dot(dir, cy.norm);
	t[2] = fabs(nl) < 1e-6 ? -1 : (dot(vsub(cy.center, orig), cy.norm) / nl);
	t[3] = fabs(nl) < 1e-6 ? -1 : (dot(vsub(cy.upc, orig), cy.norm) / nl);
	return (1);
}

int	cy_min_t_idx(t_elem cy, float *t, t_vec *h)
{
	int i;
	int minidx;

	if (t[0] > 0 && (dot(cy.norm, vsub(h[0], cy.center)) <= 0 ||
					dot(cy.norm, vsub(h[0], cy.upc)) >= 0))
		t[0] = -1;
	if (t[1] > 0 && (dot(cy.norm, vsub(h[1], cy.center)) <= 0 ||
					dot(cy.norm, vsub(h[1], cy.upc)) >= 0))
		t[1] = -1;
	if (t[2] > 0 && vlen(vsub(h[2], cy.center)) > cy.radius)
		t[2] = -1;
	if (t[3] > 0 && vlen(vsub(h[3], cy.upc)) > cy.radius)
		t[3] = -1;
	minidx = -1;
	i = -1;
	while (++i < 4)
		if (t[i] > 0 && (minidx < 0 || t[minidx] > t[i]))
			minidx = i;
	return (minidx);
}

int	cy_intersect(t_elem cy, t_vec orig, t_vec dir, t_isc *isc)
{
	float	t[4];
	t_vec	h[4];
	int		i;
	int		minidx;

	if (!cy_solve(cy, orig, dir, t))
		return (0);
	i = -1;
	while (++i < 4)
		h[i] = vadd(orig, vmul(dir, t[i]));
	minidx = cy_min_t_idx(cy, t, h);
	if (minidx < 0 || (t[minidx] > isc->obj_dist && isc->obj_dist > -1))
		return (0);
	isc->obj_dist = t[minidx];
	isc->hit = h[minidx];
	if (minidx == 2 || minidx == 3)
		isc->n = dot(dir, cy.norm) > 0 ? vmul(cy.norm, -1) : cy.norm;
	else
		isc->n = vnorm(vsub(h[minidx], vadd(cy.center,
			vmul(cy.norm, dot(cy.norm, vsub(h[minidx], cy.center))))));
	isc->mat = cy.mat;
	return (1);
}
