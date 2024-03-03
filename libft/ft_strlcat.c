/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:37:26 by dongjle2          #+#    #+#             */
/*   Updated: 2023/11/02 19:04:08 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		len_src;
	size_t		len_dst;
	size_t		chrsize;

	len_src = ft_strlen(src);
	if (!dst && !dstsize)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	chrsize = dstsize - len_dst - 1;
	dst += len_dst;
	while (chrsize-- && *src)
		*dst++ = *src++;
	*dst = 0;
	return (len_src + len_dst);
}
