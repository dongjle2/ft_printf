//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:02:57 by dongjle2          #+#    #+#             */
/*   Updated: 2023/11/14 18:46:47 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		ret_val;

	va_start(ap, s);
	ret_val = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			s += begin_rd(s, ap, &ret_val);
		}
		else
		{ 
			ft_putchar_fd(*s, 1, &ret_val);
			s++;
		}
	}
	va_end(ap);
	return (ret_val);
}

int	begin_rd(const char *s, va_list ap, int *ret_val)
{
	t_packet	k;
	char		*mem;
	size_t		mem_len;

	mem = cp_s_to_calloc(s);
	if (!mem)
		return (-1);
	rd_mem_to_pkt(&k, mem);
	prt_pkt(&k, ap, ret_val);
	mem_len = ft_strlen(mem);
	free(mem);
	return (mem_len);
}

int	rd_mem_to_pkt(t_packet *k, char *mem)
{
	size_t	i;
	char	*pmem;

	i = 0;
	pmem = mem;
	init_packet(k);
	while (!ft_strchr(FORMATS, *pmem))
	{
		check_flags(k, &pmem);
		check_width(k, &pmem);
		check_precision(k, &pmem);
	}
	check_format(k, pmem);
	return (0);
}

int	prt_pkt(t_packet *k, va_list ap, int *ret_val)
{
	t_display 	d;
	int			malloc_fail;

	malloc_fail = 0;

	if (k->fmt == 'c' || k->fmt == '%')
		malloc_fail = prt_c(k, &d, ap, ret_val);
	else if (k->fmt == 's')
		malloc_fail = prt_s(k, &d, ap, ret_val);
	else if (k->fmt == 'p')
		malloc_fail = prt_p(k, &d, ap, ret_val);
	else if (k->fmt == 'x' || k->fmt == 'X')
		malloc_fail = prt_x(k, &d, ap, ret_val);
	else if (k->fmt == 'd' || k->fmt == 'i')
		malloc_fail = prt_d(k, &d, ap, ret_val);
	else if (k->fmt == 'u')
		malloc_fail = prt_u(k, &d, ap, ret_val);
	if (malloc_fail == -1)
		return (-1);
	return (0);
}

int	prt_percent(t_packet *k, int *ret_val)
{
	char	*output_mem;

	output_mem = ft_calloc(k->width + 1, sizeof(char));
	if (!output_mem)
		return (-1);
	if (k->pad_flag)
		ft_memset(output_mem, '0', k->width);
	ft_memset(output_mem + k->width - 1, '%', 1);
	ft_putstr_fd(output_mem, 1, ret_val);
	free(output_mem);
	return (1);
}

char	*cp_s_to_calloc(const char *s)
{
	size_t	i;
	char	*mem;
	
	i = 0;
	while (!ft_strchr(FORMATS, s[i++]))
		;
	mem = ft_calloc(i + 1, sizeof(char));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s, i + 1);
	return (mem);
}

void	init_packet(t_packet *k)
{
	ft_bzero(k, sizeof(*k));
	k->width = -1;
	k->precision = -1;
	k->pstr = NULL;
}
//mult one flags are just warning in og function so I tried to make it same w og
void	check_flags(t_packet *k, char **pmem)
{
	while (ft_strchr(FLAGS, **pmem))
	{
		if (**pmem == '+' && k->plus_flag == 0)
			k->plus_flag = 1;
		else if (**pmem == ' ' && k->space_flag == 0)
			k->space_flag = 1;
		else if (**pmem == '-' && k->minus_flag == 0)
			k->minus_flag = 1;
		else if (**pmem == '#' && k->hash_flag == 0)
			k->hash_flag = 1;
		else if (**pmem == '0' && k->pad_flag == 0)
			k->pad_flag = 1;
		(*pmem)++;
	}
}

void	check_precision(t_packet *k, char **pmem)
{
	int		i;
	char	j;

	i = 0;
	j = 0;
	while (**pmem == '.')
	{
		j = 1;
		(*pmem)++;
		if (!ft_isdigit(**pmem))
		{
			k->precision = 0;
			return ;
		}
		while (ft_isdigit(**pmem))
		{
			i = i * 10 + (**pmem - '0');
			(*pmem)++;
		}
	}
	if (j == 1)
		k->precision = i;
	else
		k->precision = -1;
}

void	check_width(t_packet *k, char **pmem)
{
	int		i;
	char	j;
	
	i = 0;
	j = 0;
	if (!ft_isdigit(**pmem))
		return ;
	while (ft_isdigit(**pmem))
	{
		j = 1;
		i = i * 10 + (**pmem - '0');
		(*pmem)++;
	}
	if (j == 1)
		k->width = i;
}

void	check_format(t_packet *k, char *pmem)
{
	if (ft_strchr("pxX", *pmem))
	{
		if (*pmem == 'p')
			k->fmt = 'p';
		else if (*pmem == 'x')
			k->fmt = 'x';
		else
			k->fmt = 'X';
	}
	else if (ft_strchr("di", *pmem))
	{
		if (*pmem == 'd')
			k->fmt = 'd';
		else
			k->fmt = 'i';
	}
	else if (*pmem == 'u')
		k->fmt = 'u';
	else if (*pmem == 'c')
		k->fmt = 'c';
	else if (*pmem == '%')
		k->fmt = '%';
	else
		k->fmt = 's';
}
