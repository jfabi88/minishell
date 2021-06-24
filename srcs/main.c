/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/21 19:07:10 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_command(char **stringa, t_parse *parse, char *line)
{
	int	num;

	if (ft_strncmp(stringa[0], "echo", 5) == 0)
		num = ft_check_echo(parse);
	if (ft_strncmp(stringa[0], "pwd", 4) == 0)
		num = ft_check_pwd(parse);
	if (ft_strncmp(stringa[0], "cd", 3) == 0)
		num = ft_check_cd(parse);
	if (ft_strncmp(stringa[0], "exit", 5) == 0)
		num = ft_check_exit(stringa, parse, line);
	if (ft_strncmp(stringa[0], "export", 7) == 0)
		num = ft_check_export(parse);
	return (num);
}

static int	ft_parser(char *line)
{
	int		num;
	char	**stringa;
	t_parse	*parse;

	if (line && *line)
	{
		stringa = ft_split(line, ' ');                       //malloc
		if (stringa == NULL)
			return (-1);
		parse = ft_create_parse(stringa);                    //malloc
		if (parse == NULL)
		{
			ft_free_matrix(stringa);
			return (-1);
		}
		num = ft_check_command(stringa, parse, line);
		ft_free_matrix(stringa);                             //free
		ft_free_parse(parse);                                //free
	}
	return (num);
}

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

int	main(int argc, char *argv[], char *env[])
{
	char	*line;

	if (argc < 0 || argv == NULL)
		printf("qualcosa");								//si deve gestire l'errore
	ft_create_list_env(env);
	line = readline("# Orders, my Lord? ");
	if (line && ft_strlen(line) > 0)
		add_history(line);
	while (line != 0)
	{
		ft_parser(line);
		free(line);
		line = readline("# Orders, my Lord? ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	free(line);
	ft_free_listenv(list_env);
	ft_putstr_fd("exit", 1);
}
