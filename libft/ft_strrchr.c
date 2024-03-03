/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:18:07 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/28 19:45:41 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t				r;
	size_t				k;
	const unsigned char	*ps;

	r = ft_strlen(s);
	k = r;
	ps = (const unsigned char *)s;
	while (1 <= r)
	{
		if (ps[r - 1] == (unsigned char)c)
			return ((char *)ps + r - 1);
		r--;
	}
	if (ps[r] == (unsigned char)c)
		return ((char *)ps);
	if (!(unsigned char)c)
		return ((char *)ps + k);
	return (NULL);
}
