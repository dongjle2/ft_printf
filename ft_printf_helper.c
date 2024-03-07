/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:47:06 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/05 10:54:02 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.h"
#include "libft/libft.h"

void	ft_str_toupper(char *s)
{
	while (*s)
	{
		if ('a' <= *s && *s <= 'z')
			*s -= 32;
		s++;
	}
}

int	ft_max(long long a, long long b)
{
	if (a < b)
		return (b);
	return (a);
}

int	ft_min(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}

void	init_t_display(t_display *d)
{
	ft_bzero(d, sizeof(*d));
	d->sign = '+';
	d->itoa = (void *)0;
}
