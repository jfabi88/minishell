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

static int	ft_execute(t_parse *parse, t_list *list, t_list *var, int fd[2])
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
		num = ft_execute_command(parse, var, fd);
	return (num);
}

static int	ft_run(char *line, t_list *list, t_list *var)
{
	t_list	*parse_list;
	int		num;
	int		fd[2];

	num = 0;
	line = ft_expand(line, var);
	parse_list = ft_list_parse(line);
	while (parse_list && parse_list->next)
	{
		pipe(fd);
		if (ft_exec_pipe(parse_list->content, list, fd) == 0)
		{
			num = ft_execute(parse_list->content, list, var, fd);
			close(fd[0]);
			close(fd[1]);
			_exit (num);
		}
		parse_list = parse_list->next;
	}
	if (parse_list)
		num = ft_execute(parse_list->content, list, var, fd);
	close(fd[0]);
	close(fd[1]);
	//free(line);
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