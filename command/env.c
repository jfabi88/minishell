#include "minishell.h"

static void	ft_env(int fd, t_list *list)
{
	t_data	*p;

	while (list)
	{
		p = ((t_data *)(list->content));
		ft_putstr_fd(p->env, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(p->content, fd);
		ft_putchar_fd('\n', fd);
		list = list->next;
	}
}

int	ft_check_env(t_parse *parse, t_list *var)
{
	ft_env(1, var);
	return (0);
}
