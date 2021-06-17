/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:33:23 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/17 18:53:55 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo(char **stringa, int fd)
{
	int	i;
	int	flag;
	int	flag2;

	flag = 0;
	i = 1;
	while (stringa[i] != 0 && ft_strncmp(stringa[i], "-n", 3) == 0)
	{
		flag = 1;
		i++;
		flag2 = i;
	}
	while (stringa[i])
	{
		if ((flag == 1 && i == flag2) || (flag == 0 && i == 1))
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

static int	ft_echo_right_arrow(char **stringa)
{
	int i;
	int	fd;

	i = ft_find_strposition(">", stringa) + 1;
	fd = open(stringa[i], O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (fd < 0)
		exit (1);
	return (fd);
}

static int	ft_echo_double_right_arrow(char **stringa)
{
	int	i;
	int	fd;

	i = ft_find_strposition(">>", stringa) + 1;
	fd = open(stringa[i], O_WRONLY | O_APPEND | O_CREAT, 00755);
	if (fd < 0)
		exit (1);
	return (fd);
}

void	ft_check_echo(char **stringa)
{
	int flag;
	int fd;
	char **input;

	flag = ft_find_flag(stringa);
	fd = 1;
	if (flag == 1)
		fd = ft_echo_right_arrow(stringa);
	else if (flag == 2)
		fd = ft_echo_double_right_arrow(stringa);
	input = ft_create_strinput(stringa);				//malloc
	ft_echo(input, fd);
	ft_free_matrix(input);
	if (fd != 1)
		close(fd);
}
