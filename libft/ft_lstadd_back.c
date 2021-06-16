/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:35:51 by jfabi             #+#    #+#             */
/*   Updated: 2021/01/23 18:37:12 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cpy;

	if (lst != 0)
	{
		if (*lst == 0)
			*lst = new;
		else
		{
			cpy = ft_lstlast(*lst);
			cpy->next = new;
		}
	}
}
