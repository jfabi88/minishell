#include "minishell.h"

int	ft_check_exit(t_parse *parse, t_list *list, t_list *var)
{
	if (ft_cpy_history(list, var) == -1)
		exit (-1);
	ft_free_listenv(var);
	ft_free_parse(parse);
	ft_free_token(g_token);
	while (list)
	{
		free(list->content);
		free(list);
		list = list->next;
	}
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
