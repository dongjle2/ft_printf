/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_c_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:57:53 by dongjle2          #+#    #+#             */
/*   Updated: 2024/02/12 01:01:41 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	prt_c(t_packet *k, t_display *d, va_list ap, int *ret_val)
{
	if (k->fmt == 'c')
		k->chr = (unsigned char)va_arg(ap, int);
	else
		k->chr = '%';
	init_t_display(d);
	d->strlen = 1;
	k->width = ft_max(k->width, d->strlen);
	// ck_input_bigger(d, k);
	set_t_display(d, k);
	if (print_display(d, k, ret_val) == -1)
		return (-1);
	return (0);
}

static void	set_t_display(t_display *d, t_packet *k)
{
	d->num_space = k->width - 1;
	if (k->minus_flag == 1)
		d->space_location = 1;
}

static int	print_display(t_display *d, t_packet *k, int *ret_val)
{
	if (d->num_space && d->space_location == 0)
	{
		if (print_space(d, k, ret_val) == -1)
			return (-1);
	}
	if (d->num_zero)
	{
		if (print_padding(d, ret_val) == -1)
			return (-1);
	}
	ft_putstr_fd(&k->chr, 1, ret_val);
	if (d->num_space && d->space_location == 1)
	{
		if (print_space(d, k, ret_val) == -1)
			return (-1);
	}
	return (0);
}

static int	print_padding(t_display *d, int *ret_val)
{
	char	*buf_zero;

	buf_zero = malloc(d->num_zero);
	if (buf_zero == NULL)
		return (-1);
	ft_memset(buf_zero, '0', d->num_zero);
	ft_putstr_fd(buf_zero, 1, ret_val);
	free(buf_zero);
	return (0);
}

static int	print_space(t_display *d, t_packet *k, int *ret_val)
{
	char	*buf_space;

	buf_space = malloc(d->num_space);
	if (buf_space == NULL)
		return (-1);
	if (d->space_location == 0 && k->pad_flag)
		ft_memset(buf_space, '0', d->num_space);
	else
		ft_memset(buf_space, ' ', d->num_space);
	ft_putstr_fd(buf_space, 1, ret_val);
	free(buf_space);
	return (0);
}