/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:17:24 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/24 15:57:30 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putfd(unsigned int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	putfd(n, fd);
}

static void	putfd(unsigned int n, int fd)
{
	unsigned char	d;

	d = n % 10 + '0';
	if (n < 10)
	{
		write(fd, &d, 1);
		return ;
	}
	putfd(n / 10, fd);
	write(fd, &d, 1);
	return ;
}
