/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:05:55 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/31 11:52:49 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len_s1;
	void	*mem;

	len_s1 = ft_strlen(s1);
	mem = ft_calloc(sizeof(char), len_s1 + 1);
	if (!mem)
		return (NULL);
	return (ft_memmove(mem, s1, len_s1));
}
