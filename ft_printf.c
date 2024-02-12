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

#include "ft_printf.h"

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
	const char	*formats;
	size_t		mem_len;

	formats = "cspdiuxX%";
	mem = cp_s_to_calloc(s, formats);
	if (!mem)
		return (-1);
	rd_mem_to_pkt(&k, mem, ap, formats);
	prt_pkt(&k, ret_val);
	mem_len = ft_strlen(mem);
	free(mem);
	// if (ft_strchr(formats, *s))
	return (mem_len);
}

int	rd_mem_to_pkt(t_packet *k, char *mem, va_list ap, const char *formats)
{
	size_t	i;
	char	*pmem;

	i = 0;
	pmem = mem;
	init_packet(k);
	while (!ft_strchr(formats, *pmem))
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

	itoa = ft_numtoa(&k->val, &k->fmt);
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

int	prt_d(t_packet *k, int *ret_val)
{
	char	*output_mem;
	size_t	strlen;
	char	*itoa;

	itoa = ft_numtoa(&k->val, &k->fmt);
	strlen = ft_strlen(itoa);
	if (!strlen)
		return (1);
	if (strlen < (unsigned int)k->width)
	{
		output_mem = ft_calloc(k->width + 1, sizeof(char));
		if (!output_mem)
			return (-1);
		if (k->pad_flag)
			ft_memset(output_mem, '0', k->width);
		else
			ft_memset(output_mem, ' ', k->width);
		if (itoa[0] != '-')
		{
			if (k->pad_flag)
			{
				if (k->plus_flag)
					ft_memset(output_mem, '+', 1);
				else if (k->space_flag)
					ft_memset(output_mem, ' ', 1);
			}
			else if (k->plus_flag)
				ft_memset(output_mem, '+', 1);
		}
		else
			if (k->pad_flag)
				ft_memset(output_mem, '-', 1);
		ft_memmove(output_mem + k->width - strlen, itoa, strlen);
		ft_putstr_fd(output_mem, 1, ret_val);
		free(output_mem);
	}
	else
	{
		if (k->plus_flag)
			ft_putchar_fd('+', 1, ret_val);
		ft_putstr_fd(itoa, 1, ret_val);
	}
	free(itoa);
	return (1);
}

int	prt_p(t_packet *k, int *ret_val)
{
	char	*output_mem;
	size_t	strlen;
	char	*itoa;

	itoa = ft_numtoa(&k->val, &k->fmt);
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

int	prt_s(t_packet *k, int *ret_val)
{
	char	*output_mem;
	size_t	strlen;

	if (!k->pstr)
	{
		ft_putstr_fd("(null)", 1, ret_val);
		return (1);
	}
	if (!*k->pstr)
	{
		while (k->width--)
			ft_putchar_fd(' ', 1, ret_val);
		if (k->precision)
			return (1);
	}
	strlen = ft_strlen(k->pstr);
	if (0 < k->precision && (size_t)k->precision < strlen)
		strlen = k->precision;
	else if (!k->precision)
		return (0);

	if (strlen < (unsigned int)k->width)
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
			ft_memmove(output_mem + k->width - strlen, k->pstr, k->width);
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


int	prt_c(t_packet *k, int *ret_val)
{
	char	*output_mem;

	if (!k->chr && k->minus_flag)
	{
		ft_putchar_fd(0, 1, ret_val);
		while (k->width && --k->width)
			ft_putchar_fd(' ', 1, ret_val);
		return (1);
	}
	output_mem = ft_calloc(k->width + 1, sizeof(char));
	if (!output_mem)
		return (-1);
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
	ft_putstr_fd(output_mem, 1, ret_val);
	free(output_mem);
	return (1);
}

char	*cp_s_to_calloc(const char *s, const char *formats)
{
	size_t	i;
	char	*mem;
	
	i = 0;
	while (!ft_strchr(formats, s[i++]))
		;
	mem = ft_calloc(i + 1, sizeof(char));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s, i + 1);
	return (mem);
}

void	init_packet(t_packet *k)
{
	k->val.ull = 0;
	k->fmt = 0;
	k->plus_flag = 0;
	k->minus_flag = 0;
	k->space_flag = 0;
	k->hash_flag = 0;
	k->width = 0;
	k->pad_flag = 0;
	k->complete = 0;
	k->precision = -1;
	k->chr = 0;
	k->pstr = NULL;
}

void	check_flags(t_packet *k, char **pmem)
{
	while (ft_strchr("+ -#0", **pmem))
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
	int	i;
	int	j;

	i = 0;
	j = i;
	while (**pmem == '.')
	{
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
	if (i != j)
		k->precision = i;
}

void	check_width(t_packet *k, char **pmem)
{
	int	i;

	i = 0;
	while (ft_isdigit(**pmem))
	{
		i = i * 10 + (**pmem - '0');
		(*pmem)++;
	}
	k->width = i;
	// if (i == 0)
	// 	k->width = 1;
	// else
	// 	k->width = i;
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
		k->chr = (unsigned char)va_arg(ap, int);;
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
// #include <limits.h>
// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d\n", printf("%.s\n", ""));
// 	printf("%d\n", ft_printf("%.s\n", ""));
// 	printf("%d\n", printf(" %.s\n", ""));
// 	printf("%d\n", ft_printf(" %.s\n", ""));
// 	printf("%d\n", printf(" %.s\n", "-"));
// 	printf("%d\n", ft_printf(" %.s\n", "-"));
// 	printf("%d\n", printf(" %.1s", ""));
// 	printf("%d\n", ft_printf(" %.1s", ""));
// 	printf("%d\n", printf("%.1s ", ""));
// 	printf("%d\n", ft_printf("%.1s ", ""));
// 	printf("%d\n", printf(" %.2s %.1s ", "", "-"));
// 	printf("%d\n", ft_printf(" %.2s %.1s ", "", "-"));
// 	printf("%d\n", printf(" %.3s %.2s ", " - ", ""));
// 	printf("%d\n", ft_printf(" %.3s %.2s ", " - ", ""));
// 	printf("%d\n", printf(" %.1s %.2s %.3s %.4s ", " - ", "", "4", ""));
// 	printf("%d\n", ft_printf(" %.1s %.2s %.3s %.4s ", " - ", "", "4", ""));
// 	printf("%d\n", printf(" %.2s %.3s %.4s %.5s %.1s ", " - ", "", "4", "", "2 "));
// 	printf("%d\n", ft_printf(" %.2s %.3s %.4s %.5s %.1s ", " - ", "", "4", "", "2 "));
// 	printf("%d\n", printf("%1s", ""));
// 	printf("%d\n", ft_printf("%1s", ""));
// 	printf("%d\n", printf("%-1s", ""));
// 	printf("%d\n", ft_printf("%-1s", ""));
// 	printf("%d\n", printf(" %-2s", ""));
// 	printf("%d\n", ft_printf(" %-2s", ""));
// 	printf("%d\n", printf("%-3s ", ""));
// 	printf("%d\n", ft_printf("%-3s ", ""));
// 	printf("%d\n", printf("%-0s", ""));
// 	printf("%d\n", ft_printf("%-0s", ""));
// 	printf("%d\n", printf(" %-s ", "-"));
// 	printf("%d\n", ft_printf(" %-s ", "-"));
// 	printf("%d\n", printf("%-2s", "-"));
// 	printf("%d\n", ft_printf("%-2s", "-"));
// 	printf("%d\n", printf(" %-3s %-4s ", " - ", ""));
// 	printf("%d\n", ft_printf(" %-3s %-4s ", " - ", ""));
// 	printf("%d\n", printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", ""));
// 	printf("%d\n", ft_printf(" %-2s %-3s %-4s %-5s ", " - ", "", "4", ""));
// 	printf("%d\n", printf(" %-3s %-3s %-4s %-5s %-3s ", " - ", "", "4", "", "2 "));
// 	printf("%d\n", ft_printf(" %-3s %-3s %-4s %-5s %-3s ", " - ", "", "4", "", "2 "));

// 	return (0);
// }
// 	printf("%d\n", printf(" %.1s\n", ""));
// 	printf("%d\n", ft_printf(" %.1s\n", ""));
// 	printf("%d\n", printf("%.1s\n", ""));
// 	printf("%d\n", ft_printf("%.1s\n", ""));
// 	printf("%d\n", printf(" %.s\n", "-"));
// 	printf("%d\n", ft_printf(" %.s\n", "-"));
// 	printf("%d\n", printf(" %.2s %.1s\n", "", "-"));
// 	printf("%d\n", ft_printf(" %.2s %.1s\n", "", "-"));
// 	printf("%d\n", printf(" %.3s %.2s\n", " - ", ""));
// 	printf("%d\n", ft_printf(" %.3s %.2s\n", " - ", ""));
// 	printf("%d\n", printf(" %.1s %.2s %.3s %.4s\n", " - ", "", "4", ""));
// 	printf("%d\n", ft_printf(" %.1s %.2s %.3s %.4s\n", " - ", "", "4", ""));
// 	printf("%d\n", printf(" %.2s %.3s %.4s %.5s %.1s\n", " - ", "", "4", "", "2 "));
// 	printf("%d\n", ft_printf(" %.2s %.3s %.4s %.5s %.1s\n", " - ", "", "4", "", "2 "));

	// printf("%d\n", ft_printf("%017p\n", NULL));
	// printf("%d\n", printf("%017p\n", NULL));
	// printf("%d\n", printf(" %-2p\n", 1));
	// printf("%d\n", ft_printf(" %-2p\n", 1));
	// printf("%d\n", printf(" %-2p\n", 15));
	// printf("%d\n", ft_printf(" %-2p\n", 15));
	// printf("%d\n", printf(" %-3p\n", 16));
	// printf("%d\n", ft_printf(" %-3p\n", 16));
	// printf("%d\n", printf(" %-11p %-12p\n", INT_MIN, INT_MAX));
	// printf("%d\n", ft_printf(" %-11p %-12p\n", INT_MIN, INT_MAX));
	// printf("%d\n", printf(" %-13p %-14p\n", ULONG_MAX, -ULONG_MAX));
	// printf("%d\n", ft_printf(" %-13p %-14p\n", ULONG_MAX, -ULONG_MAX));
	// printf("%d\n", printf(" %-1p %-2p\n", 0, 0));
	// printf("%d\n", ft_printf(" %-1p %-2p\n", 0, 0));
	// printf("%d\n", printf(" %-2c ", '0'));
	// printf("%d\n", ft_printf(" %-2c ", '0'));
	// printf("%d\n", printf(" %-3c", '0' - 256));
	// printf("%d\n", ft_printf(" %-3c", '0' - 256));
	// printf("%d\n", printf("%-4c ", '0' + 256));
	// printf("%d\n", ft_printf("%-4c ", '0' + 256));
	// printf("%d\n", printf(" %-1c %-2c %-3c ", '0', 0, '1'));
	// printf("%d\n", ft_printf(" %-1c %-2c %-3c ", '0', 0, '1'));
	// printf("%d\n", printf(" %-1c %-2c %-3c ", '1', '2', '3'));
	// printf("%d\n", ft_printf(" %-1c %-2c %-3c ", '1', '2', '3'));
	// printf("%d\n", printf(" %-1c %-2c %-3c ", '2', '1', 0));
	// printf("%d\n", ft_printf(" %-1c %-2c %-3c ", '2', '1', 0));

	// int x;
	// printf("%s\n", "");
	// ft_printf("%s\n", "");
	// printf("%d\n", printf("%s", ""));
	// printf("%d\n", ft_printf("%s", ""));
	// printf("  %c\n", 0);
	// ft_printf("  %c\n", 0);
	// printf("%d\n", ft_printf("%c", 0));
	// printf("%d\n", printf("%c", 0));
	// printf("\n");
	// int ret = ft_printf("%d12%d32  % 10d", 12, 68456, -3215646);
	// printf("%d\n", ret);
	// ret = printf("%d12%d32  % 10d", 12, 68456, -3215646);
	// printf("%d\n", ret);
	// ret = ft_printf("%100p %  -10d\n", &x, x);
	// printf("%d\n", ret);
	// ret = printf("%100p %  -10d\n", &x, x);
	// printf("%d\n", ret);
	// ret = ft_printf("%  -10d\n", x);
	// printf("%d\n", ret);
	// ret = printf("%  -10d\n", x);
	// printf("%d\n", ret);
	// ret = ft_printf("%100p \n", &x);
	// printf("%d\n", ret);
	// ret = printf("%100p \n", &x);
	// printf("%d\n", ret);
	// ret = ft_printf("%0005d %c123%10s\n", x, 'a', "ewrwerqwerqwerqwerqwerqwerqwe");
	// printf("%d\n", ret);
	// ret = printf("%0005d %c123%10s\n", x, 'a', "ewrwerqwerqwerqwerqwerqwerqwe");
	// printf("%d\n", ret);
	// ret = ft_printf("%0005%\n");
	// printf("%d\n", ret);
	// ret = printf("%0005%\n");
	// printf("%d\n", ret);
// 	return (0);
// }
// #include <stdio.h>
