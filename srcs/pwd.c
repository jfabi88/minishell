#include "minishell.h"

static void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = ft_find_env(list_env, "PWD");
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
}

static int	ft_run_pwd(char **output, int fd)
{
	int	i;
	int	flag;
	int	fd_2;

	i = 0;
	fd_2 = 0;
	while (output && output[i])
	{
		flag = ft_is_flag(output[i]);
		if (fd != 1 && (flag == 1 || flag == 3))
			close (fd);
		if (flag == 1 || flag == 3)
			fd = ft_open_arrow(flag, output[i + 1]);
		else if (flag == 2)
			fd_2 = ft_open_arrow(flag, output[i + 1]);
		else if (flag == 4)
			ft_run_extra_terminal(output[i + 1]);
		if (fd < 0 || fd_2 < 0)
			return (-1);
		else if (fd_2 > 0)
			close(fd_2);
		i += 2;
	}
	ft_pwd(fd);
	return (1);
}

int	ft_check_pwd(char **stringa)
{
	char	**output;

	output = ft_create_stroutput(stringa);              //malloc
	ft_run_pwd(output, 1);
	ft_free_matrix(output);                             //free
	return (1);
}