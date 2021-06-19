#include "minishell.h"

char	*ft_find_env(t_list *list, char *str)
{
	char	*temp;

	while (list)
	{
		temp = ((t_data *)(list->content))->env;
		if (ft_strncmp(temp, str, ft_strlen(str) + 1) == 0)
			return (((t_data *)(list->content))->content);
		list = list->next;
	}
	return (NULL);
}