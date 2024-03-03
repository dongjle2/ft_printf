/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:18:07 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/28 16:35:58 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t				l;
	const unsigned char	*ps;

	ps = (const unsigned char *)s;
	while (*ps)
	{
		if (*ps == (unsigned char)c)
			return ((char *)ps);
		ps++;
	}
	if (!(unsigned char)c)
	{
		l = ft_strlen(s);
		return ((char *)s + l);
	}
	return (NULL);
}
