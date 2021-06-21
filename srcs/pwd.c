#include "minishell.h"

static void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = ft_find_env(list_env, "PWD");
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
}

int	ft_check_pwd(char **stringa)
{
	char	**output;
	int		fd;

	output = ft_create_stroutput(stringa);              //malloc
	if (output == NULL)
		return (-1);
	fd = ft_open_file(output, 1);
	if (fd == -1)
		return (-1);
	ft_pwd(fd);
	if (fd != 1)
		close (fd);
	ft_free_matrix(output);                             //free
	return (1);
}