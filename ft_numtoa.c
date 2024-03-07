/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:54:48 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/04 16:35:34 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_numtoa(t_nums val, char *fmt)
{
	char	sign;
	int		len_n;
	char	*mem;

	sign = 1;
	len_n = check_sign(&val, &sign, fmt);
	mem = malloc(len_n + 1);
	if (!mem)
		return (mem);
	mem[len_n] = 0;
	while (len_n--)
	{
		if (ft_strchr("pXx", *fmt))
		{
			mem[len_n] = "0123456789abcdef"[val.ull % 16];
			val.ull /= 16;
		}
		else
		{
			mem[len_n] = "0123456789"[val.ui % 10];
			val.ui /= 10;
		}
	}
	if (sign < 0)
		mem[0] = '-';
	return (mem);
}

int	check_sign(t_nums *val, char *sign, char *fmt)
{
	int	len_n;

	if (*fmt == 'u')
		len_n = ft_uilen(val->ui, 0, fmt);
	else if (ft_strchr("pxX", *fmt))
		len_n = ft_ulllen(val->ull, 0);
	else if ((*fmt == 'd' || *fmt == 'i') && 0 <= val->i)
		len_n = ft_ilen(val->i, 0);
	else
	{
		*sign = -1;
		val->ui *= -1;
		len_n = ft_ilen(val->i, 0) + 1;
	}
	return (len_n);
}

int	ft_ulllen(unsigned long long n, int l)
{
	if (!n)
	{
		if (!l)
			return (1);
		return (l);
	}
	return (ft_ulllen(n / 16, l + 1));
}

int	ft_ilen(int n, int l)
{
	if (!n)
	{
		if (!l)
			return (1);
		return (l);
	}
	return (ft_ilen(n / 10, l + 1));
}

int	ft_uilen(unsigned int n, int l, char *fmt)
{
	if (!n)
	{
		if (!l)
			return (1);
		return (l);
	}
	if (*fmt == 'u')
		return (ft_uilen(n / 10, l + 1, fmt));
	else
		return (ft_uilen(n / 16, l + 1, fmt));
}