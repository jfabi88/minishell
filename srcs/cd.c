#include "minishell.h"

static int	ft_cd(char *path, char *input)
{
	int		cd;
	char	*content;

	cd = chdir(path);
	if (cd == -1)
		return (ft_error(5, 0, input));
	content = ft_find_env(list_env, "PWD", 3);
	if (ft_change_env(list_env, "OLDPWD", content) == -1)
		return (-1);
	if (ft_change_env(list_env, "PWD", path) == -1)
		return (-1);
	return (1);
}

static char	*ft_run_cd(char **output)
{
	int		i;
	char	*path;

	i = 0;
	if (output && output[i])
	{
		if (output[i][0] == '/')
		{
			path = malloc(ft_strlen(output[i]) + 1);
			if (path == NULL)
				return (NULL);
			ft_strlcpy(path, output[i], ft_strlen(output[i]) + 1);
		}
		else
			path = ft_create_path(list_env, output[i]);
		i++;
	}
	if (i == 0)
		path = ft_create_home_path(list_env);
	return (path);
}

int	ft_check_cd(t_parse *parse)
{
	char	*path;
	int		fd;
	int		num;

	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	if (fd != 1)
		close (fd);
	path = ft_run_cd(parse->input);
	if (path == NULL)
		return (-1);
	num = ft_cd(path, parse->input[0]);
	free(path);
	return (num);
}
