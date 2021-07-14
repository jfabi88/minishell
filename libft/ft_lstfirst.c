#include "libft.h"

t_list	*ft_lstfirst(t_list *list)
{
	while (list && list->prev)
		list = list->prev;
	return (list);
}