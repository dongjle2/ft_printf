/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:47:06 by dongjle2          #+#    #+#             */
/*   Updated: 2024/02/09 00:49:04 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

void	init_t_display(t_display *d)
{
	ft_bzero(d, sizeof(*d));
	d->sign = '+';
	d->itoa = NULL;
}

// static size_t	get_mem_len(t_display *d, t_packet *k)
// {
// 	if (k->precision < k->width)
// 	{
// 		if (k->plus_flag || k->val.i < 0)
// 			return (k->width + 2);
// 		else
// 			return (k->width + 1);
// 	}
// 	else
// 	{
// 		if (k->plus_flag || k->val.i < 0)
// 			return (k->precision + 2);
// 		else
// 			return (k->precision + 1);
// 	}
// }