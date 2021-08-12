#include "minishell.h"

static int	ft_create_list_env(char *env[], t_list	**var)
{
	int		i;
	char	**matrix;
	t_list	*list;

	i = 0;
	while (env[i])
	{
		matrix = ft_split(env[i], '=');							//malloc
		if (matrix == NULL)
			return (-1);
		list = ft_new_datalist(matrix[0], matrix[1]);			//malloc
		if (list == 0)
		{
			ft_free_listenv(list);
			return (-1);
		}
		ft_lstadd_back(var, list);
		ft_free_matrix(matrix);									//free
		i++;
	}
	ft_setprev(var);
	return (1);
}

static int	ft_execute(t_parse *parse, t_list *list, t_list *var)
{
	int	num;

	if (ft_strncmp(parse->command, "echo", 5) == 0)
		num = ft_check_echo(parse);
	else if (ft_strncmp(parse->command, "pwd", 4) == 0)
		num = ft_check_pwd(parse, var);
	else if (ft_strncmp(parse->command, "cd", 3) == 0)
		num = ft_check_cd(parse, var);
	else if (ft_strncmp(parse->command, "exit", 5) == 0)
		num = ft_check_exit(parse, list, var);
	else if (ft_strncmp(parse->command, "export", 7) == 0)
		num = ft_check_export(parse, var);
	else if (ft_strncmp(parse->command, "env", 4) == 0)
		num = ft_check_env(parse, var);
	else if (ft_strncmp(parse->command, "unset", 4) == 0)
		num = ft_check_unset(parse, var);
	else
		num = ft_execute_command(parse, var);
	return (num);
}

static t_parse	*ft_parser(char **line, t_list *var)
{
	t_parse	*parse;

	parse = NULL;
	if (line && *line)
	{
		parse = ft_parsing(line, var);
		if (parse == NULL)
			return (NULL);
	}
	return (parse);
}

static int	ft_run(char *line, t_list *list, t_list *var)
{
	t_parse	*parse;
	int		num;

	num = 0;
	parse = ft_parser(&line, var);
	if (parse != NULL)
	{
		num = ft_execute(parse, list, var);
		ft_free_parse(parse);						//free
	}
	free(line);
	return (num);
}

int	main(int argc, char *argv[], char *env[])
{
	char			*line;
	t_list			*var;
	t_list			*list;
	struct termios	origin;

	tcgetattr(STDIN_FILENO, &origin);
	list = NULL;
	if (argc < 0 || argv == NULL)
		printf("qualcosa");								//si deve gestire l'errore
	var = NULL;
	if (ft_create_list_env(env, &var) == -1)							//malloc
		return (-1);
	if (ft_file_history(&list, var) == -1)
	{
		ft_free_listenv(var);
		return (-1);
	}
	line = ft_prompt("# Orders, my Lord? ", &list, &origin);
	while (1)
	{
		ft_run(line, list, var);
		line = ft_prompt("# Orders, my Lord? ", &list, &origin);
	}
}