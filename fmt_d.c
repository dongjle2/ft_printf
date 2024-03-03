/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:26:46 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/03 20:43:15 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void		ck_input_bigger(t_display *d, t_packet *k);
void	print_edge_case(t_display *d, t_packet *k, int *ret_val);

int	prt_d(t_packet *k, t_display *d, va_list ap, int *ret_val)
{
	k->val.i = va_arg(ap, int);
	init_t_display(d);
	ck_input_bigger(d, k);
	set_t_display(d, k);
	if (print_display(d, k, ret_val) == -1)
		return (-1);
	free(d->itoa);
	return (0);
}

static void	ck_input_bigger(t_display *d, t_packet *k)
{
	d->itoa = ft_numtoa(k->val, &k->fmt);
	d->strlen = ft_strlen(d->itoa);
	k->width = ft_max(k->width, d->strlen);
	// if (k->val.i == 0 && k->precision == 0)
	// 	k->precision = 0;
	// else if (0 <= k->val.i && (k->precision < d->strlen))
	// 	k->precision = d->strlen;
	// else if (k->val.i < 0 && (k->precision < d->strlen - 1))
	// 	k->precision = d->strlen - 1;
}

static void	set_t_display(t_display *d, t_packet *k)
{
	if (k->val.i < 0)
	{
		d->sign = '-';
		ft_memmove(d->itoa, d->itoa + 1, d->strlen);
		d->strlen--;
	}
	if (k->precision == -1 && k->pad_flag && k->minus_flag == 0)	// last condition?
	{
		d->num_zero = k->width - d->strlen;
		if (k->plus_flag || k->val.i < 0)
			d->num_zero = ft_max(d->num_zero - 1, 0);
	}
	else if (k->precision != -1)
		d->num_zero = ft_max(k->precision - d->strlen, 0);
	d->num_space = ft_max(k->width - d->num_zero - d->strlen, 0);
	if (d->sign == '-' || (0 <= k->val.i && k->plus_flag))
		d->num_space = ft_max(d->num_space - 1, 0);
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
	if (k->plus_flag || k->val.i < 0)
		ft_putchar_fd(d->sign, 1, ret_val);
	if (d->num_zero)
	{
		if (print_padding(d, ret_val) == -1)
			return (-1);
	}
	if (k->val.i == 0)
		print_edge_case(d, k, ret_val);
	else
		ft_putstr_fd(d->itoa, 1, ret_val);
	if (d->num_space && d->space_location == 1)
	{
		if (print_space(d, k, ret_val) == -1)
			return (-1);
	}
	return (0);
}
void	print_edge_case(t_display *d, t_packet *k, int *ret_val)
{
	if (k->precision == -1 || k->precision == 0)
	{
		if (d->num_zero == 0)
			ft_putstr_fd("", 1, ret_val);
		else
			ft_putstr_fd(" ", 1, ret_val);
	}
	else
		ft_putstr_fd("0", 1, ret_val);
}

static int	print_padding(t_display *d, int *ret_val)
{
	char	*buf_zero;

	buf_zero = ft_calloc(1, d->num_zero + 1);
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

	buf_space = ft_calloc(1, d->num_space + 1);
	if (buf_space == NULL)
		return (-1);
	// if (d->space_location == 0 && k->pad_flag && k->precision == -1)
	// 	ft_memset(buf_space, '0', d->num_space);
	// else
	ft_memset(buf_space, ' ', d->num_space);
	// if ((k->plus_flag || k->val.i < 0) && k->precision == -1)
	// 	ft_putchar_fd(d->sign, 1, ret_val);
	ft_putstr_fd(buf_space, 1, ret_val);
	free(buf_space);
	return (0);
}
