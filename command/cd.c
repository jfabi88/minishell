#include "minishell.h"

static int	ft_cd(char *path, char *input, int fd, int flag)
{
	int		cd;
	char	*content;

	cd = chdir(path);
	if (cd == -1)
		return (ft_error(5, 0, input));
	content = ft_find_env(g_list_env, "PWD", 3);
	if (ft_change_env(g_list_env, "OLDPWD", content) == -1)
		return (-1);
	if (ft_change_env(g_list_env, "PWD", path) == -1)
		return (-1);
	if (flag == 1)
	{
		ft_putstr_fd(ft_find_env(g_list_env, "PWD", 3), fd);
		ft_putchar_fd('\n', fd);
	}
	return (1);
}

static char	*ft_run_cd(char **output, int *flag)
{
	int		i;
	char	*path;

	i = 0;
	if (output && output[i])
	{
		if (ft_strncmp(output[i], "-", 2) == 0)
		{
			flag = 1;
			path = ft_create_minus_path(g_list_env);
		}
		else if (output[i][0] == '/')
		{
			path = malloc(ft_strlen(output[i]) + 1);
			if (path == NULL)
				return (NULL);
			ft_strlcpy(path, output[i], ft_strlen(output[i]) + 1);
		}
		else
			path = ft_create_path(g_list_env, output[i]);
		i++;
	}
	if (i == 0)
		path = ft_create_home_path(g_list_env);
	return (path);
}

int	ft_check_cd(t_parse *parse)
{
	char	*path;
	int		flag;
	int		fd;
	int		num;

	flag = 0;
	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	path = ft_run_cd(parse->input, &flag);
	if (path == NULL)
		return (-1);
	num = ft_cd(path, parse->input[0], fd, flag);
	if (fd != 1)
		close (fd);
	free(path);
	return (num);
}
