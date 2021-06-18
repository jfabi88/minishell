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
	char	**stringa;

	if (line && *line)
	{
		stringa = ft_split(line, ' ');
		ft_check_command(stringa);
	}
}

int main(void)
{
    char *line;

    line = readline("# Orders, my Lord? ");
    if (line && ft_strlen(line) > 0)
        add_history(line);
    while (line)
    {
        ft_parser(line);
        // execute(line);
        line = readline("# Orders, my Lord? ");
        if (line && ft_strlen(line) > 0)
            add_history(line);
    }
    printf("exit\n");
}
