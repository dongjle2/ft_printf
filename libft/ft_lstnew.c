/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:06:18 by dongjle2          #+#    #+#             */
/*   Updated: 2023/10/29 17:16:25 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nmem;

	nmem = malloc(sizeof(t_list));
	if (!nmem)
		return (nmem);
	nmem -> content = content;
	nmem -> next = NULL;
	return (nmem);
}
