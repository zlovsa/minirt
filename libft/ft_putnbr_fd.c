/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarolee <mcarolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:40:11 by mcarolee          #+#    #+#             */
/*   Updated: 2020/11/06 23:27:11 by mcarolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rec_output(long n, int fd)
{
	char c;

	if (n > 0)
	{
		ft_rec_output(n / 10, fd);
		c = '0' + n % 10;
		write(fd, &c, 1);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	long nb;

	nb = (n > 0) ? n : -(long)n;
	if (n < 0)
		write(fd, "-", 1);
	if (n == 0)
		write(fd, "0", 1);
	ft_rec_output(nb, fd);
}
