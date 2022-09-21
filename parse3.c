/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 00:24:59 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/02 18:10:33 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	read_pl(char **inf, t_scene *sc)
{
	t_elem *n;

	if (!(n = lst_add(&sc->objs)))
		return (0);
	ft_memcpy(n->typeid, inf[0], ft_strlen(inf[0]) + 1);
	if (!vec_try_parse(inf[1], &n->center))
		return (0);
	if (!vec_try_parse(inf[2], &n->norm) || vlen(n->norm) < 1e-6)
		return (0);
	n->norm = vnorm(n->norm);
	if (!mat_try_parse(inf + 3, &n->mat))
		return (0);
	return (1);
}

int	read_sq(char **inf, t_scene *sc)
{
	t_elem *n;

	if (!(n = lst_add(&sc->objs)))
		return (0);
	ft_memcpy(n->typeid, inf[0], ft_strlen(inf[0]) + 1);
	if (!vec_try_parse(inf[1], &n->center))
		return (0);
	if (!vec_try_parse(inf[2], &n->norm) || vlen(n->norm) < 1e-6)
		return (0);
	n->norm = vnorm(n->norm);
	n->vx = fabs(n->norm.x) == 1 ? vec(0, 1, 0) : vec(1, 0, 0);
	n->vx = cross(n->norm, n->vx);
	n->vy = cross(n->norm, n->vx);
	if (!float_try_parse(inf[3], &n->radius))
		return (0);
	if (!mat_try_parse(inf + 4, &n->mat))
		return (0);
	return (1);
}

int	read_cy(char **inf, t_scene *sc)
{
	t_elem *n;

	if (!(n = lst_add(&sc->objs)))
		return (0);
	ft_memcpy(n->typeid, inf[0], ft_strlen(inf[0]) + 1);
	if (!vec_try_parse(inf[1], &n->center))
		return (0);
	if (!vec_try_parse(inf[2], &n->norm) || vlen(n->norm) < 1e-6)
		return (0);
	n->norm = vnorm(n->norm);
	if (!float_try_parse(inf[3], &n->radius))
		return (0);
	n->radius /= 2.;
	if (!float_try_parse(inf[4], &n->height))
		return (0);
	n->upc = vadd(n->center, vmul(n->norm, n->height));
	if (!mat_try_parse(inf + 5, &n->mat))
		return (0);
	return (1);
}

int	read_tr(char **inf, t_scene *sc)
{
	t_elem *n;

	if (!(n = lst_add(&sc->objs)))
		return (0);
	ft_memcpy(n->typeid, inf[0], ft_strlen(inf[0]) + 1);
	if (!vec_try_parse(inf[1], &n->center))
		return (0);
	if (!vec_try_parse(inf[2], &n->v1))
		return (0);
	if (!vec_try_parse(inf[3], &n->v2))
		return (0);
	if (!mat_try_parse(inf + 4, &n->mat))
		return (0);
	return (1);
}

int	read_obj(char *line, int fd, t_scene *sc)
{
	char	**inf;
	int		r;

	if (!*line)
	{
		free(line);
		return (1);
	}
	inf = ft_split(line, ' ');
	free(line);
	r = ft_strcmp(*inf, "R") ? 0 : read_res(inf, sc);
	r += ft_strcmp(*inf, "A") ? 0 : read_amb(inf, sc);
	r += ft_strcmp(*inf, "c") ? 0 : read_cam(inf, sc);
	r += ft_strcmp(*inf, "l") ? 0 : read_light(inf, sc);
	r += ft_strcmp(*inf, "sp") ? 0 : read_sp(inf, sc);
	r += ft_strcmp(*inf, "pl") ? 0 : read_pl(inf, sc);
	r += ft_strcmp(*inf, "sq") ? 0 : read_sq(inf, sc);
	r += ft_strcmp(*inf, "cy") ? 0 : read_cy(inf, sc);
	r += ft_strcmp(*inf, "tr") ? 0 : read_tr(inf, sc);
	free_split(inf);
	if (!r)
		return (error("Wrong element information", fd, sc));
	return (1);
}
