#include "minishell.h"

static void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = ft_find_env(g_list_env, "PWD", 3);
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
}

int	ft_check_pwd(t_parse *parse)
{
	int		fd;

	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	ft_pwd(fd);
	if (fd != 1)
		close (fd);
	return (1);
}
