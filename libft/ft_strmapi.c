/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:08:52 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/28 21:48:49 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mem;

	i = 0;
	mem = ft_calloc(1, ft_strlen(s) + 1);
	if (!mem)
		return (mem);
	while (s[i])
	{
		mem[i] = f(i, s[i]);
		i++;
	}
	return (mem);
}
