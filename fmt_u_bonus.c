/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_u_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:26:46 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/05 11:53:02 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void		ck_input_bigger(t_display *d, t_packet *k);
static void		set_t_display(t_display *d, t_packet *k);
static int	print_display(t_display *d, t_packet *k, int *ret_val);
static int	print_padding(t_display *d, int *ret_val);
static int	print_space(t_display *d, int *ret_val);

int	prt_u(t_packet *k, t_display *d, va_list ap, int *ret_val)
{
	k->val.ui = va_arg(ap, unsigned int);
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
	if (k->val.ui == 0 && k->precision == 0)
		d->strlen = 0;
	k->width = ft_max(k->width, d->strlen);
}

static void	set_t_display(t_display *d, t_packet *k)
{
	if (k->precision == -1 && k->pad_flag && k->minus_flag == 0)	// last condition?
	{
		d->num_zero = k->width - d->strlen;
		if (k->plus_flag || k->val.ui < 0)
			d->num_zero = ft_max(d->num_zero - 1, 0);
	}
	else if (k->precision != -1)
		d->num_zero = ft_max(k->precision - d->strlen, 0);
	d->num_space = ft_max(k->width - d->num_zero - d->strlen, 0);
	if (d->sign == '-' || (0 <= k->val.ui && k->plus_flag))
		d->num_space = ft_max(d->num_space - 1, 0);
	if (k->minus_flag == 1)
		d->space_location = 1;
}

static int	print_display(t_display *d, t_packet *k, int *ret_val)
{
	if (d->num_space && d->space_location == 0)
	{
		if (print_space(d, ret_val) == -1)
			return (-1);
	}
	if (k->plus_flag || k->val.ui < 0)
		ft_putchar_fd(d->sign, 1, ret_val);
	if (d->num_zero)
	{
		if (print_padding(d, ret_val) == -1)
			return (-1);
	}
	if (!(k->val.ui == 0 && k->precision == 0))
		ft_putstr_fd(d->itoa, 1, ret_val);
	if (d->num_space && d->space_location == 1)
	{
		if (print_space(d, ret_val) == -1)
			return (-1);
	}
	return (0);
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

static int	print_space(t_display *d, int *ret_val)
{
	char	*buf_space;

	buf_space = ft_calloc(1, d->num_space + 1);
	if (buf_space == NULL)
		return (-1);
	ft_memset(buf_space, ' ', d->num_space);
	ft_putstr_fd(buf_space, 1, ret_val);
	free(buf_space);
	return (0);
}
