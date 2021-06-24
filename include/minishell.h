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

typedef struct s_parse
{
	char	**input;
	char	**output;
}				t_parse;

t_list	*list_env;

/* command */

int		ft_check_echo(t_parse *parse);
int		ft_check_pwd(t_parse *parse);
int		ft_check_cd(t_parse *parse);
int		ft_check_exit(char **stringa, t_parse *parse, char *line);
int		ft_check_export(t_parse *parse);

/* create_path */

char	*ft_create_path(t_list *list, char *str);
char	*ft_create_home_path(t_list *list);

/* env_utils.c */

char	*ft_find_env(t_list *list, char *env);
int		ft_change_env(t_list *list, char *dst, char *src);
t_list	*ft_new_datalist(char *env, char *content);
void	ft_free_listenv(t_list *env);

/* file_utils.c */

void	ft_run_extra_terminal(char *del);
int		ft_open_file(char **output, int fd);
int		ft_open_arrow(int flag, char *stringa);

/* flag_utils.c */

int		ft_find_flag(char **stringa);
char	*ft_convert_flag(int flag);
int		ft_n_flag(char **matrix);
int		ft_is_flag(char *str);

/* mtr_utils.c */

int		ft_mtrlen(char **matrix);
char	**ft_mtrlcpy(char **src, int len);
void	ft_free_matrix(char **matrix);

/* parse_utils.c */

void    ft_free_parse(t_parse *parse);
t_parse *ft_create_parse(char **stringa);

/* utils.c */

int		ft_find_strposition(char *str, char **matrix);

#endif