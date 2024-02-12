/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:33:40 by dongjle2          #+#    #+#             */
/*   Updated: 2023/11/19 23:23:54 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*prt_s_wop_wow(t_packet *k, size_t *strlen)
{
	char	*output_mem;

	output_mem = ft_calloc(*strlen + 1, sizeof(char));
	if (!output_mem)
		return (NULL);
	ft_memmove(output_mem, k->pstr, *strlen);
	return (output_mem);
}

char	*prt_s_wop_ww(t_packet *k, size_t *strlen)
{
	char	*output_mem;

	if (*strlen < k->width)
		*strlen = k->width;
	output_mem = ft_calloc(*strlen + 1, sizeof(char));
	if (!output_mem)
		return (NULL);
	if (k->minus_flag)
		ft_memmove(output_mem, k->pstr, strlen);
	else
		
	
	return (output_mem);
}

char	*prt_s_wp_wow(t_packet *k, size_t *strlen)
{
	char	*output_mem;

	if (k->precision < *strlen)
	{
		*strlen = k->precision;
		k->pstr[*strlen] = 0;
	}
	output_mem = ft_calloc(*strlen + 1, sizeof(char));
	if (!output_mem)
		return (NULL);
	
	return (output_mem);
}

char	*prt_s_wp_ww(t_packet *k, size_t *strlen)
{
	char	*output_mem;

	if (k->precision < *strlen)
	{
		*strlen = k->precision;
		k->pstr[*strlen] = 0;
	}
	output_mem = ft_calloc(k->width + 1, sizeof(char));
	if (!output_mem)
		return (NULL);
	if (*strlen < k->width)	//fill space
		
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
	if (!*k->pstr)
	{

	}
	strlen = ft_strlen(k->pstr);
	if ((k->precision != -1) && (k->width != -1))
		output_mem = prt_s_wp_ww(k, &strlen);
	else if ((k->precision == -1) && (k->width != -1))
		output_mem = prt_s_wop_ww(k, &strlen);
	else if ((k->precision != -1) && (k->width == -1))
		output_mem = prt_s_wp_wow(k, &strlen);
	else
		output_mem = prt_s_wop_wow(k, &strlen);
	if (!output_mem)
		return (-1);
//-----------------check_padding-------------------------------
	if (k->pad_flag)
		ft_memset(output_mem, '0', k->width);
	else
		ft_memset(output_mem, ' ', k->width);
//------------------check_l-justify or r-justify---------------
	if (k->minus_flag)
		ft_memmove(output_mem, k->pstr, strlen);
	else
		ft_memmove(output_mem + k->width - strlen, k->pstr, strlen);
	return (1);
}