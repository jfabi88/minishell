#include "minishell.h"

static void	ft_env(int fd, t_list *list)
{
	t_data	*p;

	while (list)
	{
		p = ((t_data*)(list->content));
		ft_putstr_fd(p->env, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(p->content, fd);
		ft_putchar_fd('\n', fd);
		list = list->next;
	}
}

int	ft_check_env(t_parse *parse)
{
	int	fd;
	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	ft_env(fd, g_list_env);
	if (fd != 1)
		close (fd);
	return (1);
}