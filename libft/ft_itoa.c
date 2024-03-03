/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:18:49 by dongjle2          #+#    #+#             */
/*   Updated: 2023/11/05 17:03:15 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long long n, int l);
static int	check_sign(long long *m, int *sign);

char	*ft_itoa(int n)
{
	int			sign;
	int			len_n;
	char		*mem;
	long long	m;

	m = (long long)n;
	len_n = check_sign(&m, &sign);
	mem = malloc(len_n);
	if (!mem)
		return (mem);
	mem[--len_n] = 0;
	while (len_n--)
	{
		mem[len_n] = (m % 10) + '0';
		m /= 10;
	}
	if (sign < 0)
		mem[0] = '-';
	return (mem);
}

static int	check_sign(long long *m, int *sign)
{
	int	len_n;

	if (0 <= *m)
	{
		*sign = 1;
		len_n = ft_intlen(*m, 0) + 1;
	}
	else
	{
		*sign = -1;
		*m *= -1;
		len_n = ft_intlen(*m, 0) + 2;
	}
	return (len_n);
}

static int	ft_intlen(long long n, int l)
{
	if (!n)
	{
		if (!l)
			return (1);
		return (l);
	}
	return (ft_intlen(n / 10, l + 1));
}
