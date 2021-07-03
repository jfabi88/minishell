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
	char	*command;
	char	**input;
	char	**output;
}				t_parse;

t_list	*list_env;

/* command */

int		ft_check_echo(t_parse *parse);
int		ft_check_pwd(t_parse *parse);
int		ft_check_cd(t_parse *parse);
int		ft_check_exit(t_parse *parse);
int		ft_check_export(t_parse *parse);

/* create_path */

char	*ft_create_path(t_list *list, char *str);
char	*ft_create_home_path(t_list *list);

/* dollar.c */

int	ft_len_dollar(char *line);
int	ft_change_dollar(char *dst, char *src);
int	ft_dollar_manager(char *line);

/* env_utils.c */

char	*ft_find_env(t_list *list, char *env, int len);
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

/* parse.c */
char	**ft_parse_lst(char *line);

/* parse_manager.c */

//int	ft_dollar(char *line, char **mtx, int *k, int *i);
int	ft_single_quote(char *line, char **mtx, int *k, int *i);
int	ft_double_quote(char *line, char **mtx, int *k, int *i);
// int	ft_red(char *line, char **mtx, int *k, int *i);
int	ft_else(char *line, char **mtx, int *k, int *i);

/* parse_utils.c */

void	ft_free_parse(t_parse *parse);
t_parse	*ft_create_parse(char **stringa);

/* utils.c */

void	*ft_free_null(void	*obj);
int		ft_find_strposition(char *str, char **matrix);
int		ft_find_next_c(char *str, char c);
int		ft_find_next_str(char *str, const char *ref);
int		ft_is_in_str(const char *str, char c);

#endif