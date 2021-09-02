#include "minishell.h"

static void	ft_null(int sign)
{
	return ;
}

static char	*ft_set_path(char **mtx, char *str)
{
	char		*path;
	int			i;
	struct stat	sb;

	i = 0;
	while (mtx[i])
	{
		path = malloc(ft_strlen(mtx[i]) + ft_strlen(str) + 2);
		if (path == NULL)
			return (NULL);
		ft_memcpy(path, mtx[i], ft_strlen(mtx[i]));
		ft_memcpy(path + ft_strlen(mtx[i]), "/", 1);
		ft_strlcpy(path + ft_strlen(mtx[i]) + 1, str, ft_strlen(str) + 1);
		if (lstat(path, &sb) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	*ft_check_path(char *str, t_list *var)
{
	char		**mtx;
	char		*path;
	struct stat	sb;

	path = malloc(ft_strlen(str) + 1);
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, str, ft_strlen(str) + 1);
	if (lstat(path, &sb) == 0)
		return (path);
	free(path);
	mtx = ft_split(ft_find_env(var, "PATH", 4), ':');
	if (mtx == NULL)
		return (NULL);
	path = ft_set_path(mtx, str);
	ft_free_matrix(mtx);
	return (path);
}

int	ft_execute_child(t_parse *parse, t_list *var)
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
	if (pid == 0)
		exit(ft_execute_child(parse, var));
	else
	{
		signal(SIGINT, ft_null);
		signal(SIGQUIT, ft_null);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}
