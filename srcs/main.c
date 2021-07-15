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

static int	ft_create_list_env(char *env[])
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
		ft_lstadd_back(&g_list_env, list);
		ft_free_matrix(matrix);									//free
		i++;
	}
	ft_setprev(&g_list_env);
	return (1);
}

static int	ft_execute(t_parse *parse, t_list *list)
{
	int	num;

	if (ft_strncmp(parse->command, "echo", 5) == 0)
		num = ft_check_echo(parse);
	else if (ft_strncmp(parse->command, "pwd", 4) == 0)
		num = ft_check_pwd(parse);
	else if (ft_strncmp(parse->command, "cd", 3) == 0)
		num = ft_check_cd(parse);
	else if (ft_strncmp(parse->command, "exit", 5) == 0)
		num = ft_check_exit(parse, list);
	else if (ft_strncmp(parse->command, "export", 7) == 0)
		num = ft_check_export(parse);
	else if (ft_strncmp(parse->command, "env", 4) == 0)
		num = ft_check_env(parse);
	else if (ft_strncmp(parse->command, "unset", 4) == 0)
		num = ft_check_unset(parse);
	else
		num = ft_execute_command(parse);
	return (num);
}

static t_parse	*ft_parser(char **line)
{
	t_parse	*parse;

	parse = NULL;
	if (line && *line)
	{
		parse = ft_parsing(line);
		if (parse == NULL)
			return (NULL);
	}
	return (parse);
}

int	main(int argc, char *argv[], char *env[])
{
	char			*line;
	t_list			*list;
	t_parse			*parse;
	struct termios	origin;

	tcgetattr(STDIN_FILENO, &origin);
	list = NULL;
	if (argc < 0 || argv == NULL)
		printf("qualcosa");								//si deve gestire l'errore
	ft_create_list_env(env);							//malloc
	if (ft_file_history(&list) == -1)
		return (-1);
	line = ft_prompt("# Orders, my Lord? ", &list, &origin);
	//line = readline("# Orders, my Lord? ");
	//if (line && ft_strlen(line) > 0)
	//	ft_change_history(line, &list);
	while (1)
	{
		parse = ft_parser(&line);						//malloc
		free(line);
		if (parse != NULL)
		{
			ft_execute(parse, list);
			ft_free_parse(parse);						//free
		}
		line = ft_prompt("# Orders, my Lord? ", &list, &origin);
		//line = readline("# Orders, my Lord? ");
		//if (line && ft_strlen(line) > 0)
		//	ft_change_history(line, &list);
	}
	free(line);
	ft_free_listenv(g_list_env);							//free
	ft_putstr_fd("exit", 1);
}
