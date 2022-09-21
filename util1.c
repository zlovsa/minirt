/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:49:58 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/01 23:25:27 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	maxf(float a, float b)
{
	return (a > b ? a : b);
}

float	minf(float a, float b)
{
	return (a < b ? a : b);
}

t_elem	*lst_add(t_elem **lst)
{
	t_elem *n;
	t_elem *t;

	if (!(n = (t_elem *)malloc(sizeof(t_elem))))
		return (n);
	n->mat.color_cf = 1;
	n->mat.spec_cf = 0;
	n->mat.refr_cf = 0;
	n->mat.spec_exp = 0;
	n->mat.refr_idx = 1;
	n->mat.refl_cf = 0;
	n->next = NULL;
	t = *lst;
	while (t && t->next)
		t = t->next;
	if (!t)
		*lst = n;
	else
		t->next = n;
	return (n);
}

int		error(char *msg, int fd, t_scene *sc)
{
	(void)sc;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (fd > -1)
		close(fd);
	free_scene(sc);
	return (0);
}

int		free_split(char **inf)
{
	int i;

	i = 0;
	while (inf[i])
		free(inf[i++]);
	free(inf);
	return (0);
}
