#include "minishell.h"

int	ft_check_exit(t_parse *parse, t_list *list)
{
	int		fd;

	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	if (fd != 1)
		close (fd);
	if (ft_cpy_history(list) == -1)
		exit (-1);
	ft_free_listenv(g_list_env);
	ft_free_parse(parse);
	while (list)
	{
		free(list->content);
		free(list);
		list = list->next;
	}
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
