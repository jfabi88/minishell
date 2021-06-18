/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:33:23 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/18 14:28:26 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo(char **stringa, int fd)
{
	int	i;
	int	flag;
	int	flag2;

	flag = 0;
	i = 0;
	while (stringa[i] != 0 && ft_strncmp(stringa[i], "-n", 3) == 0)
	{
		flag = 1;
		i++;
		flag2 = i;
	}
	while (stringa[i])
	{
		if ((flag == 1 && i == flag2) || (flag == 0 && i == 0))
			ft_putstr_fd(stringa[i], fd);
		else
		{
			ft_putchar_fd(' ', fd);
			ft_putstr_fd(stringa[i], fd);
		}
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', fd);
}

static int	ft_echo_arrow(int flag, char *stringa)
{
	int	fd;

	if (flag == 1)
		fd = open(stringa, O_WRONLY | O_CREAT | O_TRUNC, 00755);
	else if (flag == 2)
		fd = open(stringa, O_RDONLY);
	if (flag == 3)
		fd = open(stringa, O_WRONLY | O_APPEND | O_CREAT, 00755);
	if (fd < 0)
		ft_error(5, stringa);
	return (fd);
}

static void	ft_run_echo(char **input, char **output)
{
	int	i;
	int	*list_fd;

	i = 0;
	list_fd = malloc(ft_mtrlen(output) / 2 + 1);
	if (list_fd == 0)
		ft_error(1, NULL);
	while (output[i])
	{
		list_fd[i / 2] = ft_echo_arrow(ft_is_flag(output[i]), output[i + 1]);
		i += 2;
	}
	list_fd[i / 2] = 0;
	i = 0;
	while (list_fd[i])
	{
		ft_echo(input, list_fd[i]);
		close(list_fd[i++]);
	}
	if (list_fd[0] == 0)
		ft_echo(input, 1);
	free(list_fd);
}

void	ft_check_echo(char **stringa)
{
	char	**input;
	char	**output;
	
	input = ft_create_strinput(stringa);				//malloc
	output = ft_create_stroutput(stringa);				//malloc
	ft_run_echo(input, output);
	ft_free_matrix(input);								//free
	ft_free_matrix(output);								//free
}
