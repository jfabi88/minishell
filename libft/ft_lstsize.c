/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:44:49 by jfabi             #+#    #+#             */
/*   Updated: 2021/01/23 18:45:08 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*cpy;

	if (lst == 0)
		return (0);
	size = 1;
	cpy = lst;
	while (cpy->next != 0)
	{
		cpy = cpy->next;
		size++;
	}
	return (size);
}
