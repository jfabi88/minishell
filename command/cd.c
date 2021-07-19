#include "minishell.h"

static int	ft_cd(char *path, char *input, t_list *var)
{
	int		cd;
	char	*content;

	cd = chdir(path);
	if (cd == -1)
		return (ft_error(5, 0, input));
	content = ft_find_env(var, "PWD", 3);
	if (ft_find_env(var, "OLDPWD", 6) == NULL)
	{
		if (ft_create_env(var, "OLDPWD", content) == -1)
			return (-1);
	}
	else
	{
		if (ft_change_env(var, "OLDPWD", content) == -1)
			return (-1);
	}
	if (ft_change_env(var, "PWD", path) == -1)
		return (-1);
	return (1);
}

static char	*ft_run_cd(char **output, t_list *var)
{
	int		i;
	char	*path;

	i = 1;
	if (output && output[i])
	{
		if (ft_strncmp(output[i], "-", 2) == 0)
			path = ft_create_minus_path(var);
		else if (output[i][0] == '/')
		{
			path = malloc(ft_strlen(output[i]) + 1);
			if (path == NULL)
				return (NULL);
			ft_strlcpy(path, output[i], ft_strlen(output[i]) + 1);
		}
		else
			path = ft_create_path(var, output[i]);
		i++;
	}
	if (i == 1)
		path = ft_create_home_path(var);
	return (path);
}

static int	ft_check_flag(char **input)
{
	int	flag;

	flag = 0;
	if (input[1] == NULL)
		return (0);
	else if (ft_strncmp(input[1], "-", 2) == 0)
		flag = 1;
	return (flag);
}

int	ft_check_cd(t_parse *parse, t_list *var)
{
	char	*path;
	int		flag;
	int		fd;
	int		num;

	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	flag = ft_check_flag(parse->input);
	path = ft_run_cd(parse->input, var);
	if (path == NULL)
		return (-1);
	num = ft_cd(path, parse->input[1], var);
	if (flag == 1)
	{
		ft_putstr_fd(ft_find_env(var, "PWD", 3), fd);
		ft_putchar_fd('\n', fd);
	}
	if (fd != 1)
		close (fd);
	free(path);
	return (num);
}
