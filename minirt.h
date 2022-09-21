/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:39:31 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/02 18:16:16 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct	s_vec
{
	float x;
	float y;
	float z;
}				t_vec;

typedef struct	s_mat
{
	t_vec color;
	float color_cf;
	float spec_exp;
	float spec_cf;
	float refr_idx;
	float refr_cf;
	float refl_cf;
}				t_mat;

typedef struct	s_isc
{
	t_vec orig;
	t_vec dir;
	t_vec hit;
	t_vec n;
	t_mat mat;
	float obj_dist;
}				t_isc;

typedef struct	s_elem
{
	char			typeid[5];
	t_vec			center;
	t_vec			norm;
	float			radius;
	float			height;
	t_vec			v1;
	t_vec			v2;
	float			brightness;
	float			fov;
	t_mat			mat;
	int				resx;
	int				resy;
	t_vec			vx;
	t_vec			vy;
	float			tgx;
	float			tgy;
	t_vec			upc;
	struct s_elem	*next;
}				t_elem;

typedef struct	s_scene
{
	t_elem	*res;
	t_elem	*ambient;
	t_elem	*cams;
	t_elem	*objs;
	t_elem	*lights;
	t_vec	*img;
}				t_scene;

/*
** vectors1.c
*/

t_vec			vec(float x, float y, float z);
t_vec			vsub(t_vec lhs, t_vec rhs);
t_vec			vadd(t_vec lhs, t_vec rhs);
t_vec			vmul(t_vec lhs, float k);
float			vlen(t_vec v);

/*
** vectors2.c
*/

float			dot(t_vec lhs, t_vec rhs);
t_vec			cross(t_vec a, t_vec b);
t_vec			vnorm(t_vec l);
t_vec			color_mul(t_vec a, t_vec b);

/*
** intersect1.c
*/

int				cy_intersect(t_elem cy, t_vec orig, t_vec dir, t_isc *isc);

/*
** intersect2.c
*/

int				sp_intersect(t_elem sp, t_vec orig, t_vec dir, t_isc *isc);
int				pl_intersect(t_elem sp, t_vec orig, t_vec dir, t_isc *isc);
int				sq_intersect(t_elem sp, t_vec orig, t_vec dir, t_isc *isc);
int				tr_intersect(t_elem sp, t_vec orig, t_vec dir, t_isc *isc);

/*
** parse1.c
*/

int				int_try_parse(char *str, int *out);
int				float_try_parse(char *str, float *out);
int				vec_try_parse(char *str, t_vec *out);
int				mat_try_parse(char **str, t_mat *out);

/*
** parse2.c
*/

int				read_res(char **inf, t_scene *sc);
int				read_amb(char **inf, t_scene *sc);
int				read_cam(char **inf, t_scene *sc);
int				read_light(char **inf, t_scene *sc);
int				read_sp(char **inf, t_scene *sc);

/*
** parse3.c
*/

int				read_pl(char **inf, t_scene *sc);
int				read_sq(char **inf, t_scene *sc);
int				read_cy(char **inf, t_scene *sc);
int				read_tr(char **inf, t_scene *sc);
int				read_obj(char *line, int fd, t_scene *sc);

/*
** savebmp.c
*/

int				savebmp(t_scene *sc);

/*
** ray.c
*/

int				scene_intersect(t_vec orig, t_vec dir, t_scene sc, t_isc *isc);
t_vec			cast_ray(t_vec orig, t_vec dir, t_scene sc, int level);
t_vec			get_dir(t_scene *sc, t_elem *cam, int i, int j);
void			render(t_scene *sc, t_elem *cam);

/*
** light1.c
*/

int				in_shadow(t_isc isc, t_elem *light, t_scene sc, t_vec *l_dir);
void			diff_spec_light(t_scene sc,
					t_isc isc, t_vec *d_light, t_vec *s_light);

/*
** light2.c
*/

t_vec			reflect(t_vec i, t_vec n);
t_vec			refract(t_vec i, t_vec n, float eta_t, float eta_i);
t_vec			reflect_color(t_scene sc, t_isc isc, int level);
t_vec			refract_color(t_scene sc, t_isc isc, int level);

/*
** util1.c
*/

int				free_split(char **inf);
t_elem			*lst_add(t_elem **lst);
int				error(char *msg, int fd, t_scene *sc);
float			maxf(float a, float b);
float			minf(float a, float b);

/*
** util2.c
*/

void			lst_free(t_elem **lst);
void			free_scene(t_scene *sc);

#endif
