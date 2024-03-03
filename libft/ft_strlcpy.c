/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:42:17 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/24 14:43:44 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		len_src;
	size_t		chrsize;

	len_src = ft_strlen(src);
	if (dstsize <= 0)
		return (len_src);
	chrsize = dstsize - 1;
	while (chrsize-- && *src)
		*dst++ = *src++;
	*dst = 0;
	return (len_src);
}
