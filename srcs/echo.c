/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:33:23 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/19 16:34:48 by jfabi            ###   ########.fr       */
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

static int	ft_run_echo(char **input, char **output, int fd)
{
	int	i;
	int	flag;
	int	fd_2;

	i = 0;
	fd_2 = 0;
	while (output && output[i])
	{
		flag = ft_is_flag(output[i]);
		if (fd != 1 && (flag == 1 || flag == 3))
			close (fd);
		if (flag == 1 || flag == 3)
			fd = ft_open_arrow(flag, output[i + 1]);
		else if (flag == 2)
			fd_2 = ft_open_arrow(flag, output[i + 1]);
		else if (flag == 4)
			ft_run_extra_terminal(output[i + 1]);
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
	ft_run_echo(input, output, 1);
	ft_free_matrix(input);                               //free
	ft_free_matrix(output);                              //free
}
