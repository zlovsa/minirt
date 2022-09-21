/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 00:06:04 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 15:07:50 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	int_try_parse(char *str, int *out)
{
	long sign;
	long rv;

	if (!str)
		return (0);
	rv = 0;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '+' || *str == '-') ? 1 : 0;
	while ('0' <= *str && *str <= '9')
		rv = rv * 10 + sign * (*str++ - '0');
	if (*str)
		return (0);
	*out = rv;
	return (1);
}

int	float_try_parse(char *str, float *out)
{
	float sign;
	float rv;
	float tenp;

	if (!str)
		return (0);
	rv = 0;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '+' || *str == '-') ? 1 : 0;
	while ('0' <= *str && *str <= '9')
		rv = rv * 10 + sign * (*str++ - '0');
	str += *str == '.' ? 1 : 0;
	tenp = 10;
	while ('0' <= *str && *str <= '9')
	{
		rv += sign * (*str++ - '0') / tenp;
		tenp *= 10;
	}
	if (*str)
		return (0);
	*out = rv;
	return (1);
}

int	vec_try_parse(char *str, t_vec *out)
{
	char	**s;
	int		r;

	s = ft_split(str, ',');
	r = float_try_parse(s[0], &out->x) &&
		float_try_parse(s[1], &out->y) &&
		float_try_parse(s[2], &out->z) && !s[3];
	free_split(s);
	return (r);
}

int	mat_coefs_try_parse(char **str, t_mat *out)
{
	int		p;
	char	**s;

	if (str[1])
	{
		s = ft_split(str[1], ',');
		p = s && float_try_parse(s[0], &out->color_cf) &&
			float_try_parse(s[1], &out->spec_cf) &&
			float_try_parse(s[2], &out->refr_cf) &&
			float_try_parse(s[3], &out->spec_exp) &&
			float_try_parse(s[4], &out->refr_idx) &&
			float_try_parse(s[5], &out->refl_cf) && !s[6];
		free_split(s);
		if (!p || str[2])
			return (0);
	}
	return (1);
}

int	mat_try_parse(char **str, t_mat *out)
{
	char	**s;
	int		r;
	int		g;
	int		b;
	int		p;

	if (!str)
		return (0);
	s = ft_split(*str, ',');
	p = s && int_try_parse(s[0], &r) &&
		int_try_parse(s[1], &g) &&
		int_try_parse(s[2], &b) && !s[3];
	free_split(s);
	if (!p)
		return (0);
	out->color = vec(r / 255., g / 255., b / 255.);
	return (mat_coefs_try_parse(str, out));
}
