/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 00:19:52 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 14:54:38 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	read_res(char **inf, t_scene *sc)
{
	if (sc->res || !lst_add(&sc->res))
		return (0);
	if (!int_try_parse(inf[1], &sc->res->resx))
		return (0);
	if (!int_try_parse(inf[2], &sc->res->resy))
		return (0);
	if (inf[3])
		return (0);
	//check negative, large, etc
	return (1);
}

int	read_amb(char **inf, t_scene *sc)
{
	if (sc->ambient || !lst_add(&sc->ambient))
		return (0);
	if (!float_try_parse(inf[1], &sc->ambient->brightness))
		return (0);
	if (!mat_try_parse(inf + 2, &sc->ambient->mat))
		return (0);
	return (1);
}

int	read_cam(char **inf, t_scene *sc)
{
	t_elem *n;

	if (!(n = lst_add(&sc->cams)))
		return (0);
	if (!vec_try_parse(inf[1], &n->center))
		return (0);
	if (!vec_try_parse(inf[2], &n->norm) || vlen(n->norm) < 1e-6)
		return (0);
	n->norm = vnorm(n->norm);
	n->vx = fabs(n->norm.y) == 1 ? vec(1, 0, 0) : vec(0, 1, 0);
	n->vx = cross(n->norm, n->vx);
	n->vy = cross(n->vx, n->norm);
	if (!float_try_parse(inf[3], &n->fov))
		return (0);
	return (!inf[4]);
}

int	read_light(char **inf, t_scene *sc)
{
	t_elem *n;

	if (!(n = lst_add(&sc->lights)))
		return (0);
	if (!vec_try_parse(inf[1], &n->center))
		return (0);
	if (!float_try_parse(inf[2], &n->brightness))
		return (0);
	if (!mat_try_parse(inf + 3, &n->mat))
		return (0);
	return (1);
}

int	read_sp(char **inf, t_scene *sc)
{
	t_elem *n;

	if (!(n = lst_add(&sc->objs)))
		return (0);
	ft_memcpy(n->typeid, inf[0], ft_strlen(inf[0]) + 1);
	if (!vec_try_parse(inf[1], &n->center))
		return (0);
	if (!float_try_parse(inf[2], &n->radius))
		return (0);
	if (!mat_try_parse(inf + 3, &n->mat))
		return (0);
	return (1);
}
