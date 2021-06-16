/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/06/16 16:12:08 by jfabi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(char *line)
{
	char	**commands;
	int		i;

	i = 0;
	commands = ft_split(line, ';');										//malloc
	while (commands[i])
	{
		
	}
}

int	main(void)
{
	char *line;
	char *stringa;
	int n;

	n = 1;
	while (n > 0)
	{
		write(1, "# : ", 4);
		n = ft_get_next_line(0, &line);									//malloc
		ft_parser(line);
		printf("stringa: %s\ncaratteri letti: %d\n", line, n);
	}
	printf("stringa: %s\ncaratteri letti: %d\n", line, n);
}