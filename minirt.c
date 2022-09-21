/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:42:06 by mcarolee          #+#    #+#             */
/*   Updated: 2021/02/02 18:01:01 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_scene *sc)
{
	sc->res = NULL;
	sc->ambient = NULL;
	sc->cams = NULL;
	sc->objs = NULL;
	sc->lights = NULL;
	sc->img = NULL;
}

int		check_scene(t_scene *sc, int gnl)
{
	if (gnl < 0)
		return (error("Cannot read file", -1, sc));
	if (!sc->res || !sc->ambient || !sc->cams)
		return (error("Not enough information", -1, sc));
	return (1);
}

int		read_scene(int ac, char **av, t_scene *sc)
{
	int		fd;
	int		gnl;
	char	*line;

	if (ac < 2)
		return (error("Filename missing", -1, sc));
	if ((ac == 3 && ft_strcmp(av[2], "--save")) || ac > 3)
		return (error("Wrong parameters", -1, sc));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (error("Cannot open file", -1, sc));
	init_scene(sc);
	while ((gnl = get_next_line(fd, &line)) > -1)
	{
		if (!read_obj(line, fd, sc))
			return (0);
		if (!gnl)
			break ;
	}
	close(fd);
	return (check_scene(sc, gnl));
}

int		main(int ac, char **av)
{
	t_scene sc;

	if (!read_scene(ac, av, &sc))
		return (1);
	render(&sc, sc.cams);
	if (ac == 3)
		savebmp(&sc);
	// else
	// 	(void)ac;
	free_scene(&sc);
	return (0);
}
