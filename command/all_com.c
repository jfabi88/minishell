#include "minishell.h"

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

static char	*ft_check_path(char *str)
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
	mtx = ft_split(ft_find_env(g_list_env, "PATH", 4), ':');
	if (mtx == NULL)
		return (NULL);
	path = ft_set_path(mtx, str);
	ft_free_matrix(mtx);
	return (path);
}

int	ft_execute_command(t_parse *parse)
{
	int		pid;
	char	*path;
	char	**mtx;

	pid = fork();
	if (pid == 0)
	{
		path = ft_check_path(parse->command);
		if (path != NULL)
		{
			mtx = ft_lst_to_mtx(g_list_env);
			if (execve(path, parse->input, mtx) == -1)
				printf("ciao\n");
			ft_free_matrix(mtx);
			free(path);
		}
		_exit (1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (1);
	}
}
