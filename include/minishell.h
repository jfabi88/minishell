#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h"

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

t_list	*g_list_env;

/* COMMAND */

int		ft_check_echo(t_parse *parse);
int		ft_check_pwd(t_parse *parse);
int		ft_check_cd(t_parse *parse);
int		ft_check_env(t_parse *parse);
int		ft_check_exit(t_parse *parse, t_list *list);
int		ft_check_export(t_parse *parse);

/* PARSE */

/* parse.c */

char	**ft_parse_lst(char **line);

/* parse_check.c */

int		ft_parse_check(char *line);

/* parse_dollar.c */

char	*ft_dollar_manager(char *line);

/* parse_manager.c */

int		ft_create_str_parse(char **mtx, char *line);

/* parse_utils.c */

void	ft_free_parse(t_parse *parse);
t_parse	*ft_create_parse(char **stringa);

/* SRCS */

/* create_path */

char	*ft_create_path(t_list *list, char *str);
char	*ft_create_home_path(t_list *list);

/* env_utils.c */

char	*ft_find_env(t_list *list, char *env, int len);
int		ft_change_env(t_list *list, char *dst, char *src);
t_list	*ft_new_datalist(char *env, char *content);
void	ft_free_listenv(t_list *env);

/* error */

int		ft_error(int id, char c, char *str);

/* file_utils.c */

void	ft_run_extra_terminal(char *del);
int		ft_open_file(char **output, int fd);
int		ft_open_arrow(int flag, char *stringa);

/* flag_utils.c */

int		ft_find_flag(char **stringa);
char	*ft_convert_flag(int flag);
int		ft_n_flag(char **matrix);
int		ft_is_flag(char *str);

/* history.c */

int		ft_cpy_history(t_list *list);
int		ft_change_history(char *line, t_list **list);
int		ft_file_history(void);

/* mtr_utils.c */

int		ft_mtrlen(char **matrix);
char	**ft_mtrlcpy(char **src, int len);
void	*ft_free_matrix(char **matrix);

/* utils.c */

char	**ft_lst_to_mtx(t_list *list);
void	*ft_free_null(void	*obj);
int		ft_find_strposition(char *str, char **matrix);

/* utils_2.c */

int		ft_between_c(char *str, int c_pos, char c);
int		ft_find_next_c(char *str, int start, char c);
int		ft_find_next_str(char *str, const char *ref);
int		ft_is_in_str(const char *str, char c);

#endif