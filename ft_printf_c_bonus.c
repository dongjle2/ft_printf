/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 00:55:39 by dongjle2          #+#    #+#             */
/*   Updated: 2023/11/18 22:01:34 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	prt_c_null_given(t_packet *k, int *ret_val)
{
	if (k->minus_flag || k->width)
	{
		if (k->minus_flag)
		{
			ft_putchar_fd(0, 1, ret_val);
			while (--k->width)
				ft_putchar_fd(' ', 1, ret_val);
		}
		else
		{
			while (--k->width)
				ft_putchar_fd(' ', 1, ret_val);
			ft_putchar_fd(0, 1, ret_val);
		}
	}
	else
		ft_putchar_fd(0, 1, ret_val);
}

void	prt_c_core(t_packet *k, char *output_mem)
{
	if (k->minus_flag)
	{
		ft_memset(output_mem, k->chr, 1);
		ft_memset(output_mem + 1, ' ', k->width - 1);
	}
	else
	{
		if (1 < k->pad_flag)
			ft_memset(output_mem, '0', k->width);
		else
			ft_memset(output_mem, ' ', k->width);
		ft_memset(output_mem + k->width - 1, k->chr, 1);
	}
}

int	prt_c(t_packet *k, int *ret_val)
{
	char	*output_mem;

	if (k->width == -1)
		k->width = 1;
	if (!k->chr)
	{
		prt_c_null_given(k, ret_val);
		return (1);
	}
	output_mem = ft_calloc(k->width + 1, sizeof(char));
	if (!output_mem)
		return (-1);
	prt_c_core(k, output_mem);
	ft_putstr_fd(output_mem, 1, ret_val);
	free(output_mem);
	return (1);
}