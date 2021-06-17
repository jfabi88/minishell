#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"

/* command.c */

void	ft_check_echo(char **stringa);

/* utils.c */

int	ft_find_flag(char **stringa);
int	ft_find_strposition(char *str, char **matrix);

#endif