/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:02:47 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/02 18:13:11 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	lst_free(t_elem **lst)
{
	t_elem *t;
	t_elem *n;

	n = *lst;
	while (n)
	{
		t = n->next;
		free(n);
		n = t;
	}
	*lst = NULL;
}

void	free_scene(t_scene *sc)
{
	lst_free(&sc->ambient);
	lst_free(&sc->cams);
	lst_free(&sc->lights);
	lst_free(&sc->objs);
	lst_free(&sc->res);
	free(sc->img);
}
