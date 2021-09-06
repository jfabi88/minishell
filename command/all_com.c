#include "minishell.h"

static int	ft_execute_child(t_parse *parse, t_list *var)
{
	int		ret;
	char	*path;
	char	**mtx;

	path = ft_check_path(parse->command, var);
	if (path != NULL)
	{
		mtx = ft_lst_to_mtx(var);
		ret = execve(path, parse->input, mtx);
		if (ret < 0)
			ft_putstr_fd(strerror(errno), 2);
		ft_free_matrix(mtx);
		free(path);
	}
	else
	{
		ft_putstr_fd(": command not found: ", 2);
		ft_putstr_fd(parse->command, 2);
		ft_putstr_fd("\n", 2);
		return (127);
	}
	return (ret);
}

int	ft_execute_command(t_parse *parse, t_list *var)
{
	int		pid;
	int		status;
	char	*path;
	char	**mtx;

	pid = fork();
	signal(SIGINT, ft_null);
	signal(SIGQUIT, ft_null);
	if (pid == 0)
		exit(ft_execute_child(parse, var));
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}
