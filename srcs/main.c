/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarzano <lmarzano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/07/03 16:57:15 by lmarzano         ###   ########.fr       */
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
		ft_lstadd_back(&list_env, list);
		ft_free_matrix(matrix);									//free
		i++;
	}
	return (1);
}

static int	ft_execute(t_parse *parse)
{
	int	num;

	if (ft_strncmp(parse->command, "echo", 5) == 0)
		num = ft_check_echo(parse);
	if (ft_strncmp(parse->command, "pwd", 4) == 0)
		num = ft_check_pwd(parse);
	if (ft_strncmp(parse->command, "cd", 3) == 0)
		num = ft_check_cd(parse);
	if (ft_strncmp(parse->command, "exit", 5) == 0)
		num = ft_check_exit(parse);
	if (ft_strncmp(parse->command, "export", 7) == 0)
		num = ft_check_export(parse);
	return (num);
}

static t_parse	*ft_parser(char **line)
{
	char	**stringa;
	t_parse	*parse;

	parse = NULL;
	if (line && *line)
	{
		stringa = ft_parse_lst(line);
		//stringa = ft_split(*line, ' ');                       //malloc / parsing starts here! / change split with ad hoc func
		if (stringa == NULL)
			return (NULL);
		parse = ft_create_parse(stringa);                    //malloc
		ft_free_matrix(stringa);                             //free
	}
	return (parse);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_parse	*parse;

	if (argc < 0 || argv == NULL)
		printf("qualcosa");								//si deve gestire l'errore
	ft_create_list_env(env);							//malloc
	line = readline("# Orders, my Lord? ");
	if (line && ft_strlen(line) > 0)
		add_history(line);
	while (line != 0)
	{
		parse = ft_parser(&line);						//malloc
		free(line);
		if (parse != NULL)
		{
			ft_execute(parse);
			ft_free_parse(parse);						//free
		}
		line = readline("# Orders, my Lord? ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	free(line);
	ft_free_listenv(list_env);							//free
	ft_putstr_fd("exit", 1);
}
