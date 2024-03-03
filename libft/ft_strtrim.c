/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:14:45 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/31 12:07:24 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*mem;
	size_t	l_idx;
	size_t	r_idx;

	if (!ft_strlen(s1))
		return (ft_strdup(""));
	if (!ft_strlen(set))
		return (ft_strdup(s1));
	l_idx = 0;
	r_idx = ft_strlen(s1) - 1;
	while (ft_strchr((const char *)set, s1[l_idx]))
		l_idx++;
	while (ft_strchr((const char *)set, s1[r_idx]) && r_idx)
		r_idx--;
	if (l_idx <= r_idx)
	{
		mem = (char *)ft_calloc(1, r_idx - l_idx + 2);
		if (!mem)
			return (mem);
	}
	else
		return (ft_strdup(""));
	return (ft_memmove(mem, s1 + l_idx, r_idx - l_idx + 1));
}
