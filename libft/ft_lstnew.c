/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:44:13 by jfabi             #+#    #+#             */
/*   Updated: 2021/01/23 18:44:25 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*diz;

	diz = 0;
	diz = (t_list *)malloc(sizeof(*diz));
	if (diz == 0)
		exit (0);
	diz->content = content;
	diz->next = 0;
	return (diz);
}
