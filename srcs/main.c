/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/19 17:23:33 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_command(char **stringa)
{
	if (ft_strncmp(stringa[0], "echo", 5) == 0)
		ft_check_echo(stringa);
	if (ft_strncmp(stringa[0], "pwd", 4) == 0)
		ft_check_pwd(stringa);
	if (ft_strncmp(stringa[0], "cd", 3) == 0)
		ft_check_cd(stringa);
}

static void	ft_parser(char *line)
{
	char	**stringa;

	if (line && *line)
	{
		stringa = ft_split(line, ' ');                       //malloc
		ft_check_command(stringa);
		ft_free_matrix(stringa);                             //free
	}
}

static t_list	*ft_new_datalist(char *str)
{
	int		size;
	int		size2;
	t_data	*data;
	t_list	*list;

	data = malloc(sizeof(t_data *));
	if (data == NULL)
		return (NULL);
	size2 = ft_strlen(ft_strchr(str, '='));
	size = ft_strlen(str) - size2;
	data->env = malloc(size + 1);
	if (data->env == NULL)
		return (NULL);
	ft_strlcpy(data->env, str, size + 1);
	data->content = malloc(size2);
	if (data->content == NULL)
		return (NULL);
	ft_strlcpy(data->content, str + size + 1, size2 + 1);
	list = ft_lstnew(data);
	return (list);
}

static int	ft_create_list_env(char *env[])
{
	int		i;
	t_list	*list;

	i = 0;
	while (env[i])
	{
		list = ft_new_datalist(env[i]);			//malloc
		if (list == 0)
			return (-1);
		ft_lstadd_back(&list_env, list);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;

	if (argc < 0 || argv == NULL)
		printf("");
	ft_create_list_env(env);
	line = readline("# Orders, my Lord? ");
	if (line && ft_strlen(line) > 0)
		add_history(line);
	while (line && ft_strncmp(line, "exit", 5) != 0)
	{
		ft_parser(line);
		free(line);
		line = readline("# Orders, my Lord? ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
	}
	free(line);
	ft_free_listenv(list_env);
	printf("exit\n");
}
