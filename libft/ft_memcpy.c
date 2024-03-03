/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:11:36 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/24 16:06:08 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p_d;
	unsigned char	*p_s;

	if (dst == src)
		return (dst);
	p_d = (unsigned char *)dst;
	p_s = (unsigned char *)src;
	while (n--)
		*p_d++ = *p_s++;
	return (dst);
}
