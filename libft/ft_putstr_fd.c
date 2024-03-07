/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:58:38 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/07 13:41:55 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd, int *ret_val)
{
	while (*s)
	{
		if (ft_putchar_fd(*s, fd, ret_val) == -1)
			return (-1);
		s++;
	}
}
