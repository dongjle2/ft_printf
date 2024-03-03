/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:04:06 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/31 11:53:42 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	void	*mem;

	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_strdup(""));
	if (len_s + 1 <= start + len)
		len = len_s - start;
	mem = ft_calloc(len + 1, sizeof(char));
	if (!mem)
		return (mem);
	return (ft_memmove(mem, s + start, len));
}
