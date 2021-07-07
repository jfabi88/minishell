#include "minishell.h"

static void	ft_free_lst(t_list **list)
{
	t_list	*p;
	t_list	*n;

	p = (*list)->prev;
	n = (*list)->next;
	ft_free_data((t_data *)((*list)->content));
	p->next = n;
	if (n != NULL)
		n->prev = p;
	free (*list);
}

static int	ft_unset(t_list *list, char *parse)
{
	t_data	*p;
	t_data	*p_prev;

	if (parse == NULL)
		return (-1);
	while (list)
	{
		p = ((t_data *)(list->content));
		if (list->prev != NULL)
			p_prev = ((t_data *)(list->prev->content));
		if (ft_strncmp(p->env, parse, ft_strlen(parse) + 1) == 0)
			ft_free_lst(&list);
		list = list->next;
	}
	if (!list)
		return (-1);
	return (1);	
}

int	ft_check_unset(t_parse *parse)
{
	int	fd;
	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	if (ft_unset(g_list_env, parse->input[0]) == -1)
		return (-1);
	if (fd != 1)
		close (fd);
	return (1);
}
