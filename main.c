/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/17 15:04:51 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_command(char **stringa)
{
	if (ft_strncmp(stringa[0], "echo", 5) == 0)
		ft_check_echo(stringa);
}

static void	ft_parser(char *line)
{
	char	**commands;
	char	**stringa;
	int		i;

	i = 0;
	commands = ft_split(line, ';');										//malloc
	while (commands[i])
	{
		stringa = ft_split(commands[i], ' ');
		ft_check_command(stringa);
		i++;
	}
}

int	main(void)
{
	char	*line;
	char	*stringa;
	int		n;

	n = 1;
	while (n > 0)
	{
		write(1, "# : ", 4);
		n = ft_get_next_line(0, &line);					//malloc
		ft_parser(line);
		//printf("stringa: %s\ncaratteri letti: %d\n", line, n);
	}
	//printf("stringa: %s\ncaratteri letti: %d\n", line, n);
}