#include "minishell.h"

static int	ft_create_export(char *str)
{
	char	**matrix;
	int		ret;
	t_list	*list;

	ret = 1;
	matrix = ft_split(str, '=');
	if (matrix == NULL)
		return (-1);
	if (ft_find_env(g_list_env, matrix[0], ft_strlen(matrix[0])) == NULL)
	{
		list = ft_new_datalist(matrix[0], matrix[1]);
		if (list == NULL)
			ret = -1;
		else
			ft_lstadd_back(&g_list_env, list);
	}
	else
		ret = ft_change_env(g_list_env, matrix[0], matrix[1]) == -1;
	ft_free_matrix(matrix);
	return (ret);
}

static int	ft_check_export_format(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0)
		return (-1);
	while (ft_isalnum(str[i]))
		i++;
	if (str[i] == 0)
		return (2);
	else if (str[i] != '=')
		return (-1);
	i++;
	while (ft_isalnum(str[i]))
		i++;
	if (str[i] != 0)
		return (-1);
	return (1);
}

static int	ft_run_export(char **str)
{
	int	i;
	int	flag;

	i = 0;
	while (str[i])
	{
		flag = ft_check_export_format(str[i]);
		if (flag == -1)
			return (ft_error(6, 0, str[i]));
		else if (flag == 1)
		{
			if (ft_create_export(str[i]) == -1)
				return (ft_error(6, 0, str[i]));
		}
		i++;
	}
	return (1);
}

int	ft_check_export(t_parse *parse)
{
	char	**new_var;
	int		fd;

	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	if (fd != 1)
		close (1);
	new_var = ft_calloc(3, sizeof(char *));       //malloc
	if (new_var == NULL)
		return (-1);
	ft_run_export(parse->input);
	ft_free_matrix(new_var);                      //free
	return (1);
}