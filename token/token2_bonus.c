#include "minishell.h"

static int	ft_add_token(char *line, t_list **list)
{
	t_list	*list_tmp;
	t_token	*tmp;

	tmp = ft_tokanizer(line);
	if (tmp == NULL)
		return (-1);
	list_tmp = ft_lstnew(tmp);
	if (list_tmp == NULL)
	{
		ft_free_token(tmp);
		return (-1);
	}
	ft_lstadd_back(list, list_tmp);
	return (1);
}

static char	*ft_create_command(char *line, int *indx)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] == '&' || line[i] == '|')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '(')
	{
		len = ft_next_pare(line + i) + 1;
		ret = ft_m_strlcpy(line + i, len + 1);
	}
	else
	{
		len = ft_next_flag(line + i);
		ret = ft_m_strlcpy(line + i, len + 1);
	}
	*indx += len + i;
	return (ret);
}

static int	ft_create_commands(char *line, t_list **listone)
{
	int		i;
	char	*tmp;
	t_list	*list;

	i = 0;
	list = 0;
	while (line && line[i])
	{
		tmp = ft_create_command(line + i, &i);
		if (tmp == NULL)
		{
			ft_lstdelone(*listone, free);
			return (-1);
		}
		list = ft_lstnew(tmp);
		if (list == NULL)
		{
			ft_lstdelone(*listone, free);
			return (-1);
		}
		ft_lstadd_back(listone, list);
		while (line[i] == ' ')
			i++;
	}
	return (1);
}

int	ft_list_token(char *line, t_list **list)
{
	t_list	*list_string;
	t_list	*pointer;

	list_string = NULL;
	if (ft_create_commands(line, &list_string) == -1)
		return (-1);
	pointer = list_string;
	while (list_string)
	{
		if (ft_add_token(list_string->content, list) == -1)
		{
			ft_free_list(pointer);
			while (*list)
			{
				ft_free_token((*list)->content);
				free((*list));
				(*list) = (*list)->next;
				return (-1);
			}
		}
		list_string = list_string->next;
	}
	ft_free_list(pointer);
	return (1);
}
