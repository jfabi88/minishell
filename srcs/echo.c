/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:33:23 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/19 13:02:25 by jfabi            ###   ########.fr       */
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
	while (stringa && stringa[i] != 0 && ft_strncmp(stringa[i], "-n", 3) == 0)
	{
		flag = 1;
		i++;
		flag2 = i;
	}
	while (stringa && stringa[i])
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
		printf("#: %s. No such file or directory\n", stringa);
	return (fd);
}

static void	ft_run_echo_terminal(char *del)
{
	int		pid;
	int		status;
	char	*line;

	pid = fork();
	if (pid < 0)
		printf("");									//si deve gestire l'errore
	else if (pid == 0)
	{
		line = readline("> ");
		while (line)
		{
			if (ft_strncmp(line, del, ft_strlen(del) + 1) == 0)
				exit(0);
			line = readline("> ");
		}
	}
	else
		wait(&status);
}

static int	ft_run_echo(char **input, char **output)
{
	int	i;
	int	fd;
	int	fd_2;

	i = 0;
	fd = 1;
	fd_2 = 0;
	while (output && output[i])
	{
		if (fd != 1)
			close (fd);
		if (ft_is_flag(output[i]) == 1 || ft_is_flag(output[i]) == 3)
			fd = ft_echo_arrow(ft_is_flag(output[i]), output[i + 1]);
		else if (ft_is_flag(output[i]) == 2)
			fd_2 = ft_echo_arrow(ft_is_flag(output[i]), output[i + 1]);
		else if (ft_is_flag(output[i]) == 4)
			ft_run_echo_terminal(output[i + 1]);
		if (fd < 0 || fd_2 < 0)
			return (-1);
		else if (fd_2 > 0)
			close(fd_2);
		i += 2;
	}
	ft_echo(input, fd);
	return (1);
}

void	ft_check_echo(char **stringa)
{
	char	**input;
	char	**output;

	input = ft_create_strinput(stringa);                 //malloc
	output = ft_create_stroutput(stringa);               //malloc
	ft_run_echo(input, output);
	ft_free_matrix(input);                               //free
	ft_free_matrix(output);                              //free
}
