#include "minishell.h"

int	ft_exec_pipe(t_parse *data, t_list *env, int fd[2])
{
    int		fork_id;

	fork_id = fork();
	if (fork_id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
		return (0);
	}
	else if (fork_id == -1)
		return (-1);
	else
	{
		waitpid(fork_id, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		return (1);
	}
}

static void ft_list_pipe(char *line, t_list **list)
{
    int     i;
    int     j;
    char    *tmp;
    t_list  *ret;

    i = 0;
    j = 0;
    ret = NULL;
    while (line[i])
    {
        if (line[i] == '|' && !ft_is_in_quotes(line, i, '\'', '"'))
        {
            tmp = ft_m_strlcpy(line + j, i - j + 1);
            if (tmp ==  NULL)
                return (ft_free_list(ret));
            ft_lst_add_content(tmp, &ret, 2);
            j = i + 1;
        }
        i++;
    }
    tmp = ft_m_strlcpy(line + j, i - j + 1);
    if (tmp == NULL)
        return (ft_free_list(ret));
    ft_lst_add_content(tmp, &ret, 2);
    *list = ret;
}

t_list  *ft_list_parse(char *line)
{
    t_list  *pipe_list;
    t_list  *ret;
    t_parse	*parse;

    pipe_list = NULL;
    ret = NULL;
    ft_list_pipe(line, &pipe_list);
    free(line);
    while (pipe_list)
    {
        parse = ft_parsing(pipe_list->content);
        ft_lst_add_content(parse, &ret, 2);
        pipe_list = pipe_list->next;
    }
    ft_free_list(pipe_list);
    return (ret);
}