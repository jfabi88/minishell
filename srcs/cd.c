#include "minishell.h"

static int	ft_cd(char *path, char *input)
{
	int	cd;

	cd = chdir(path);
	if (cd == -1)
	{
		ft_putstr_fd("#: cd: ",2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	ft_change_env(list_env, "OLDPWD", ft_find_env(list_env, "PWD"));
	ft_change_env(list_env, "PWD", path);
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

int	ft_check_cd(char **stringa)
{
	char	**input;
	char	**output;
	char	*path;
	int		fd;

	input = ft_create_strinput(stringa);
	output = ft_create_stroutput(stringa);
	if (input == NULL || output == NULL)
		return (-1);
	fd = ft_open_file(output, 1);
	if (fd == -1)
		return (-1);
	if (fd != 1)
		close (fd);
	path = ft_run_cd(input);
	if (path == NULL)
		return (-1);
	ft_cd(path, input[0]);
	free(path);
	ft_free_matrix(input);
	ft_free_matrix(output);
	return (1);
}