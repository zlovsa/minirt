/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savebmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:02:17 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 23:09:49 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	colornorm(float a)
{
	if (a > 1)
		a = 1.;
	if (a < 0)
		a = 0.;
	return (a);
}

t_vec	vec_to_color(t_vec v)
{
	float maxv;

	maxv = maxf(v.x, maxf(v.y, v.z));
	if (maxv > 1)
		v = vmul(v, 1. / maxv);
	v.x = 255 * colornorm(v.x);
	v.y = 255 * colornorm(v.y);
	v.z = 255 * colornorm(v.z);
	return (v);
}

char	*bmp_header(int resx, int resy, int *rowpad, int *filesize)
{
	char *bmp;

	*rowpad = resx * 3 % 4 ? 4 - resx * 3 % 4 : 0;
	*filesize = (resx + *rowpad) * resy * 3 + 54;
	if (!(bmp = (char *)malloc(*filesize)))
		return (bmp);
	ft_bzero(bmp, *filesize);
	bmp[0] = 'B';
	bmp[1] = 'M';
	*(int *)(bmp + 2) = *filesize;
	bmp[10] = 54;
	bmp[14] = 40;
	*(int *)(bmp + 18) = resx;
	*(int *)(bmp + 22) = resy;
	bmp[26] = 1;
	bmp[28] = 24;
	return (bmp);
}

void	write_rgb(t_scene *sc, char *bmp, int rowpad)
{
	int		i;
	int		x;
	int		y;
	t_vec	color;

	i = 54;
	y = sc->res->resy;
	while (--y >= 0)
	{
		x = -1;
		while (++x < sc->res->resx)
		{
			color = vec_to_color(sc->img[y * sc->res->resx + x]);
			bmp[i++] = color.z;
			bmp[i++] = color.y;
			bmp[i++] = color.x;
		}
		i += rowpad;
	}
}

int		savebmp(t_scene *sc)
{
	char	*bmp;
	int		filesize;
	int		fd;
	int		rowpad;
	ssize_t	wr;

	if (!(bmp = bmp_header(sc->res->resx, sc->res->resy, &rowpad, &filesize)))
		return (error("Save bmp malloc error", -1, sc));
	write_rgb(sc, bmp, rowpad);
	if ((fd = open("scene.bmp", O_WRONLY | O_CREAT, 0777)) < 0)
		return (error("Save bmp cannot create file", -1, sc));
	wr = write(fd, bmp, filesize);
	free(bmp);
	close(fd);
	if (wr < filesize)
		return (error("Save bmp error write file", -1, sc));
	return (1);
}
