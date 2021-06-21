/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:33:23 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/21 19:09:29 by jfabi            ###   ########.fr       */
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

int	ft_check_echo(char **stringa)
{
	char	**input;
	char	**output;
	int		fd;

	input = ft_create_strinput(stringa);                 //malloc
	output = ft_create_stroutput(stringa);               //malloc
	if (input == NULL || output == NULL)
		return (-1);
	fd = ft_open_file(output, 1);
	if (fd == -1)
		return (-1);
	ft_echo(input, fd);
	if (fd != 1)
		close (fd);
	ft_free_matrix(input);                               //free
	ft_free_matrix(output);                              //free
	return (1);
}
