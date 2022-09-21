/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 00:20:33 by mcarolee          #+#    #+#             */
/*   Updated: 2021/01/29 15:18:47 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*get_list(t_list **all, int fd)
{
	t_list *t;

	if ((t = *all))
		while (t && t->fd != fd)
			t = t->next;
	if (t || !(t = (t_list*)malloc(sizeof(t_list))))
		return (t);
	t->next = *all;
	t->fd = fd;
	if (!(t->tail = ft_strdup("")))
	{
		free(t);
		return (NULL);
	}
	*all = t;
	return (t);
}

int		read_to_lf(char **str, int fd)
{
	char *buf;
	long rcnt;
	char *tmp;

	if (ft_strchr(*str, '\n'))
		return (1);
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (!ft_strchr(*str, '\n') && (rcnt = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rcnt] = 0;
		tmp = *str;
		if (!(*str = ft_strjoin(*str, buf)))
		{
			free(buf);
			return (-1);
		}
		free(tmp);
	}
	free(buf);
	return (rcnt);
}

int		split(char **line, char **tail)
{
	long l;
	long i;
	char *t;

	l = 0;
	while ((*tail)[l] && (*tail)[l] != '\n')
		l++;
	if (!(*line = (char *)malloc(l + 1)))
		return (-1);
	i = 0;
	while (i < l)
	{
		(*line)[i] = (*tail)[i];
		i++;
	}
	(*line)[l] = 0;
	if (!(t = ft_strdup(((*tail)[l]) ? (*tail + l + 1) : "")))
		return (-1);
	free(*tail);
	*tail = t;
	return (1);
}

void	del_fd(t_list **all, t_list *del)
{
	t_list *t;
	t_list *p;

	p = NULL;
	t = *all;
	while (t != del)
	{
		p = t;
		t = t->next;
	}
	if (p)
		p->next = t->next;
	else
		*all = t->next;
	free(t);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*all;
	t_list			*cur;
	int				rcnt;

	if (BUFFER_SIZE < 1 || fd < 0 || !line || !(cur = get_list(&all, fd)))
		return (-1);
	if ((rcnt = read_to_lf(&(cur->tail), fd)) < 0)
	{
		*line = NULL;
		free(cur->tail);
		del_fd(&all, cur);
		return (-1);
	}
	if (!rcnt)
	{
		*line = cur->tail;
		del_fd(&all, cur);
		return (0);
	}
	return (split(line, &(cur->tail)));
}
