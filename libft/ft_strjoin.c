/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:10:50 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/31 12:01:23 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*mem;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	mem = malloc(len_s1 + len_s2 + 1);
	if (!mem)
		return (mem);
	ft_memmove(mem, s1, len_s1);
	ft_memmove(mem + len_s1, s2, len_s2 + 1);
	return (mem);
}
