/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:46:04 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/26 17:58:43 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*ps1;
	const unsigned char	*ps2;

	if (!n)
		return (0);
	n--;
	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	while (*ps1 && *ps2 && n--)
	{
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
		ps1++;
		ps2++;
	}
	return (*ps1 - *ps2);
}
