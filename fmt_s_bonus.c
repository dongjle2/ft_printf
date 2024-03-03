/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_s_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:56:17 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/02 23:14:04 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void		ck_input_bigger(t_display *d, t_packet *k);

int	prt_s(t_packet *k, t_display *d, va_list ap, int *ret_val)
{
	k->pstr = va_arg(ap, char *);
	if (k->pstr == 0)
		k->pstr = "(null)";
	init_t_display(d);
	ck_input_bigger(d, k);
	set_t_display(d, k);
	if (print_display(d, k, ret_val) == -1)
		return (-1);
	return (0);
}

static void	ck_input_bigger(t_display *d, t_packet *k)
{
	d->strlen = ft_strlen(k->pstr);
	if (k->precision == -1)
	{
		if (ft_strncmp(k->pstr, "(null)", 6) == 0)
			k->precision = 6;
		else
			k->precision = d->strlen;
	}
	k->precision = ft_min(k->precision, d->strlen);
	// if (k->precision < d->strlen)
	// 	d->strlen = k->precision;
	k->width = ft_max(k->width, k->precision);
}

static void	set_t_display(t_display *d, t_packet *k)
{
	// d->num_zero = ft_max(k->precision - d->strlen, 0);
	d->num_space = ft_max(k->width - k->precision - d->prefix, 0);
	if (k->minus_flag == 1)
		d->space_location = 1;
}

static int	print_display(t_display *d, t_packet *k, int *ret_val)
{
	char 	*buf_display;

	buf_display = ft_calloc(k->precision + 1, 1);
	if (buf_display == NULL)
		return (-1);
	ft_memmove(buf_display, k->pstr, k->precision);
	if (d->num_space && d->space_location == 0)
	{
		if (print_space(d, k, ret_val) == -1)
			return (-1);
	}
	ft_putstr_fd(buf_display, 1, ret_val);
	if (d->num_space && d->space_location == 1)
	{
		if (print_space(d, k, ret_val) == -1)
			return (-1);
	}
	free(buf_display);
	return (0);
}

static int	print_space(t_display *d, t_packet *k, int *ret_val)
{
	char	*buf_space;

	buf_space = ft_calloc(d->num_space + 1, 1);
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
