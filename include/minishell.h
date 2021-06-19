#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_data
{
	char	*env;
	char	*content;
}				t_data;

t_list	*list_env;

/* command.c */

void	ft_check_echo(char **stringa);
int		ft_check_pwd(char **stringa);
void	ft_check_cd(char **stringa);

/* utils.c */

int		ft_find_flag(char **stringa);
int		ft_find_strposition(char *str, char **matrix);
char	*ft_convert_flag(int flag);
int		ft_n_flag(char **matrix);

/* utils2.c */

int		ft_is_flag(char *str);
char	**ft_create_strinput(char **matrix);
char	**ft_create_stroutput(char **mat);
void	ft_free_listenv(t_list *env);
void	ft_run_extra_terminal(char *del);

/* utils3.c */

char	*ft_find_env(t_list *list, char *str);

/* utils_mtr.c */

int		ft_mtrlen(char **matrix);
void	ft_free_matrix(char **matrix);
char	**ft_mtrlcpy(char **src, int len);
int		ft_open_arrow(int flag, char *stringa);

#endif