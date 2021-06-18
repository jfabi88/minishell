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

int		ft_find_flag(char **stringa);
int		ft_find_strposition(char *str, char **matrix);
char	*ft_convert_flag(int flag);
int		ft_n_flag(char **matrix);

/* utils2.c */

int		ft_is_flag(char *str);
char	**ft_create_strinput(char **matrix);
char	**ft_create_stroutput(char **mat);

/* utils_mtr.c */

int		ft_mtrlen(char **matrix);
void	ft_free_matrix(char **matrix);
char	**ft_mtrlcpy(char **src, int len);

/* error.c */

void	ft_error_mat(char **mat, int nmb, char *str);
void	ft_error(int nmb, char *str);

#endif