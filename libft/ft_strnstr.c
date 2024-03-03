/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:24:55 by dongjle2          #+#    #+#             */
/*   Updated: 2023/11/15 13:57:13 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (!*needle)
		return ((char *)haystack);
	len_needle = ft_strlen(needle);
	while (l < len && haystack[i])
	{
		if (haystack[i] == *needle && l + len_needle <= len)
			if (ft_strncmp(haystack + i, needle, len_needle) == 0)
				return ((char *)haystack + i);
		i++;
		l++;
	}
	return (NULL);
}
