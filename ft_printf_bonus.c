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
	rd_mem_to_pkt(&k, mem, ap);
	prt_pkt(&k, ret_val);
	mem_len = ft_strlen(mem);
	free(mem);
	return (mem_len);
}

int	rd_mem_to_pkt(t_packet *k, char *mem, va_list ap)
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
	check_format(ap, k, pmem);
	return (0);
}

void	prt_pkt(t_packet *k, int *ret_val)
{

	if (k->fmt == 'c') 
		prt_c(k, ret_val);
	else if (k->fmt == 's')
		prt_s(k, ret_val);
	else if (k->fmt == 'p')
		prt_p(k ,ret_val);
	else if (k->fmt == 'x' || k->fmt == 'X')
		prt_xX(k, ret_val);
	else if (ft_strchr("dui", k->fmt))
		prt_d(k, ret_val);
	else if (k->fmt == '%')
		prt_percent(k, ret_val);
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

int	prt_xX_hard(t_packet *k, char **output_mem, size_t strlen, char *itoa)
{
	*output_mem = ft_calloc(k->width + 1, sizeof(char));
	if (!*output_mem)
		return (-1);
	if (k->pad_flag)
	{
		ft_memset(*output_mem, '0', k->width);
		if (k->hash_flag)
			ft_memmove(*output_mem, "0x", 2);
	}
	else
	{
		ft_memset(*output_mem, ' ', k->width);
		if (k->hash_flag)
			ft_memmove(*output_mem + k->width - strlen - 2, "0x", 2);
	}
	ft_memmove(*output_mem + k->width - strlen, itoa, strlen);
	return (1);
}

int	prt_xX_ez(char **output_mem, size_t strlen, char *itoa)
{
	*output_mem = ft_calloc(strlen + 1, sizeof(char));
	if (!*output_mem)
		return (-1);
	ft_memmove(*output_mem, itoa, strlen);
	return (1);
}

int	prt_xX(t_packet *k, int *ret_val)
{
	char	*output_mem;
	size_t	strlen;
	char	*itoa;

	itoa = ft_numtoa(k->val, &k->fmt);
	strlen = ft_strlen(itoa);
	if (!strlen)
		return (1);
	if (strlen < (unsigned int)k->width)
		prt_xX_hard(k, &output_mem, strlen, itoa);
	else
		prt_xX_ez(&output_mem, strlen, itoa);
	if (k->fmt == 'X')
		ft_str_toupper(output_mem);
	ft_putstr_fd(output_mem, 1, ret_val);
	free(itoa);
	free(output_mem);
	return (1);
}

int	prt_p(t_packet *k, int *ret_val)
{
	char	*output_mem;
	size_t	strlen;
	char	*itoa;

	itoa = ft_numtoa(k->val, &k->fmt);
	strlen = ft_strlen(itoa);
	if (!strlen)
		return (1);
	if (strlen + 2 <= (unsigned int)k->width)
		output_mem = prt_p_hard(k, strlen, itoa);
	else
		output_mem = prt_p_ez(ret_val, strlen, itoa);
	ft_putstr_fd(output_mem, 1, ret_val);
	free(itoa);
	free(output_mem);
	return (1);
}

char	*prt_p_hard(t_packet *k, size_t strlen, char *itoa)
{
	char	*output_mem;

	output_mem = ft_calloc(k->width + 1, sizeof(char));
	if (!output_mem)
		return (NULL);
	if (k->minus_flag)
	{
		ft_memset(output_mem, ' ', k->width);
		ft_memmove(output_mem, "0x", 2);
		ft_memmove(output_mem + 2, itoa, strlen);
	}
	else if (k->pad_flag)
	{
		ft_memmove(output_mem, "0x", 2);
		ft_memset(output_mem + 2, '0', k->width - strlen - 2);
		ft_memmove(output_mem + k->width - strlen, itoa, strlen);
	}
	else
	{
		ft_memset(output_mem, ' ', k->width);
		ft_memmove(output_mem + k->width - strlen - 2, "0x", 2);
		ft_memmove(output_mem + k->width - strlen, itoa, strlen);
	}
	return (output_mem);
}

char	*prt_p_ez(int *ret_val, size_t strlen, char *itoa)
{
	char	*output_mem;
	
	output_mem = ft_calloc(strlen + 1, sizeof(char));
	if (!output_mem)
		return (NULL);
	*ret_val += write(1, "0x", 2);
	ft_memmove(output_mem, itoa, strlen);
	return (output_mem);
}

// int	prt_s_empty_s(t_packet *k, int *ret_val)
// {
// 	if (k->width == -1)
// 		return (1);
// 	while (k->width--)
// 		ft_putchar_fd(' ', 1, ret_val);
// 	if (k->precision)
// 		return (1);
// }

void	prt_s_w_precision(t_packet *k, size_t *strlen, int *ret_val)
{
	int	width;

	width = k->width;
	if (0 < k->precision && (size_t)k->precision < *strlen)
		*strlen = k->precision;
	else if (!k->precision)
	{
		while (0 < width--)
		{
			ft_putchar_fd(' ', 1, ret_val);
			k->width--;
		}
	}
}

int	prt_s_nullptr_wo_prcs(t_packet *k, int *ret_val)
{
	int	cnt_space;

	if (k->width < 6)
	{
		ft_putstr_fd(k->pstr, 1, ret_val);
		return (1);
	}
	else if (6 <= k->width)
	{
		cnt_space = k->width - 6;
		if (k->minus_flag)
		{
			ft_putstr_fd(k->pstr, 1, ret_val);
			while (cnt_space--)
				ft_putchar_fd(' ', 1, ret_val);
		}
		else
		{
			while (cnt_space--)
				ft_putchar_fd(' ', 1, ret_val);
			ft_putstr_fd(k->pstr, 1, ret_val);
		}
	}
	return (1);
}

int	prt_s_nullptr(t_packet *k, int *ret_val)
{
	int	cnt_space;

	k->pstr = "(null)";
	prt_s_nullptr_wo_prcs(k, ret_val);
	if (k->width < 6  && k->precision == -1)
	{
		ft_putstr_fd(k->pstr, 1, ret_val);
		return (1);
	}
	else if (k->width && k->precision == -1)
	{
		cnt_space = k->width - 6;
		if (k->minus_flag)
		{
			ft_putstr_fd(k->pstr, 1, ret_val);
			while (cnt_space--)
				ft_putchar_fd(' ', 1, ret_val);
		}
		else
		{
			while (cnt_space--)
				ft_putchar_fd(' ', 1, ret_val);
			ft_putstr_fd(k->pstr, 1, ret_val);
			return (1);
		}
	}
	else if (k->width && k->precision == 0)
	{
		*ret_val += k->width;
		return (1);
	}
	else if (!k->width)
		return (1);
	return (1);
}

int	prt_s(t_packet *k, int *ret_val)
{
	char	*output_mem;
	size_t	strlen;

	if (!k->pstr)
	{
		if (prt_s_nullptr(k, ret_val) == 1)
			return (1);
	}
		// k->pstr = "(null)";
		// if (k->width && k->precision == -1)
		// {

		// 	while (k->width--)
		// 		ft_putstr_fd(' ', 1, ret_val);
		// 	ft_putstr_fd(k->pstr, 1, ret_val);
		// 	return (1);
		// }
		// else if (k->width && k->precision == 0)
		// {
		// 	*ret_val += k->width;
		// 	return (1);
		// }
		// else if (!k->width)
		// 	return (1);
	if (!*k->pstr)
	{
		if (k->width == -1)
			return (1);
		while (k->width--)
			ft_putchar_fd(' ', 1, ret_val);
		if (k->precision)
			return (1);
	}
	strlen = ft_strlen(k->pstr);
	if ((k->precision != -1) && (k->width != -1))
	{

	}
	else if ((k->precision == -1) && (k->width != -1))
	{

	}
	else if ((k->precision != -1) && (k->width == -1))
	{
		
	}
	else
	{

	}
	if (k->pad_flag)
	if (k->precision != -1)
	{
		prt_s_w_precision(k, &strlen, ret_val);
		if (!k->precision)
			return (1);
	}
	if (k->width == -1)
		k->width = strlen;
	if (strlen < (size_t)k->width)
	{
		output_mem = ft_calloc(k->width + 1, sizeof(char));
		if (!output_mem)
			return (-1);
		if (k->minus_flag)
		{
			// if (!*k->pstr)
			// {
			// 	while (k->width--)
			// 		ft_putchar_fd(' ', 1, ret_val);
			// 	return (1);
			// }
			ft_memset(output_mem, ' ', k->width);
			ft_memmove(output_mem, k->pstr, strlen);
		}
		else
		{
			if (k->pad_flag)
				ft_memset(output_mem, '0', k->width);
			else
				ft_memset(output_mem, ' ', k->width);
			ft_memmove(output_mem + k->width - strlen, k->pstr, strlen);
		}
	}
	else
	{
		output_mem = ft_calloc(strlen + 1, sizeof(char));
		if (!output_mem)
			return (-1);
		ft_memmove(output_mem, k->pstr, strlen);
	}
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

void	check_format(va_list ap, t_packet *k, char *pmem)
{
	if (ft_strchr("pxX", *pmem))
	{
		k->val.ull = va_arg(ap, unsigned long long);
		if (*pmem == 'p')
			k->fmt = 'p';
		else if (*pmem == 'x')
			k->fmt = 'x';
		else
			k->fmt = 'X';
	}
	else if (ft_strchr("di", *pmem))
	{
		k->val.i = va_arg(ap, int);
		if (*pmem == 'd')
			k->fmt = 'd';
		else
			k->fmt = 'i';
	}
	else if (*pmem == 'u')
	{
		k->val.ui = va_arg(ap, unsigned int);
		k->fmt = 'u';
	}
	else if (*pmem == 'c')
	{
		k->chr = (unsigned char)va_arg(ap, int);
		k->fmt = 'c';
	}
	else if (*pmem == '%')
	{
		k->chr = '%';
		k->fmt = '%';
	}
	else
	{
		k->pstr = va_arg(ap, char *);
		k->fmt = 's';
	}
	if (k->fmt != 's' && k->width == 0)
		k->width = 1;
}
#include <limits.h>
#include <stdio.h>
int	main(void)
{
	int x;

	// printf("%d\n", x = ft_printf("% 2.1d\n", -1000));
	// printf("\n");
	// printf("%d\n", x = printf("% 2.1d\n", -1000));
	// printf("\n");
	// printf("%d\n", x = ft_printf("% 10.3d\n", -1000));
	// printf("\n");
	// printf("%d\n", x = printf("% 10.3d\n", -1000));
	// printf("\n");
	ft_printf("%+10.3d\n", -1000);
	printf("%+10.3d\n", -1000);
	// ft_printf("%10.3d\n", 1000);
	// printf("%10.3d\n", 1000);
	// ft_printf("%+10.3d\n", 1000);
	// printf("%+10.3d\n", 1000);
	// ft_printf("%10.3d\n", -1000);
	// printf("%10.3d\n", -1000);
	return (0);
}