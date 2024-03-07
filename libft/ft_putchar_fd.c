/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:54:04 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/07 13:39:27 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putchar_fd(char c, int fd, int *ret_val)
{
	ssize_t	written;

	written = write(fd, &c, 1);
	if (written == -1)
		return (-1);
	*ret_val += written;
}
