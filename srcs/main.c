/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/07/09 11:20:41 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	ft_run_commands(t_token *token, int num, t_list *var, t_list *list)
{
	t_list	*commands;
	t_list	*flag;

	commands = token->commands;
	flag = token->flag;
	while (commands)
	{
		if (num == 1 && ft_strncmp(flag->content, "&&", 3) == 0)
			num = ft_running(commands->content, list, var);
		else if (num == 0 && ft_strncmp(flag->content, "||", 3) == 0)
			num = ft_running(commands->content, list, var);
		commands = commands->next;
		flag = flag->next;
	}
	return (num);
}

static int	ft_run_s_commands(t_token *token, int num, t_list *var, t_list *list)
{
	t_list	*commands;
	t_list	*flag;

	commands = token->s_commands;
	flag = token->s_flag;
	while (commands)
	{
		if (num == 1 && ft_strncmp(flag->content, "&&", 3) == 0)
			num = ft_running(commands->content, list, var);
		else if (num == 0 && ft_strncmp(flag->content, "||", 3) == 0)
			num = ft_running(commands->content, list, var);
		commands = commands->next;
		flag = flag->next;
	}
	return (num);
}

int	ft_running(t_token *token, t_list *list, t_list *var)
{
	t_parse	*parse;
	int		num;

	parse = ft_parser(&token->line, var);
	if (parse != NULL)
	{
		num = ft_execute(parse, list, var);
		ft_free_parse(parse);						//free
	}
	num = ft_run_s_commands(token, num, var, list);
	num = ft_run_commands(token, num, var, list);
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
		g_token = ft_tokanizer(line);
		free(line);
		ft_running(g_token, list, var);
		ft_free_token(g_token);
		line = ft_prompt("# Orders, my Lord? ", &list, &origin);
	}
}
