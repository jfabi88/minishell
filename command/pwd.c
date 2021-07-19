#include "minishell.h"

static void	ft_pwd(int fd, t_list *var)
{
	char	*pwd;

	pwd = ft_find_env(var, "PWD", 3);
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
}

int	ft_check_pwd(t_parse *parse, t_list *var)
{
	int		fd;

	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	ft_pwd(fd, var);
	if (fd != 1)
		close (fd);
	return (1);
}
