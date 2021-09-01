#include "minishell.h"

void	ft_set_dup(int fd[2], int flag)
{
	if (flag == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (flag == 1)
	{
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		close (fd[1]);
		close(fd[0]);
	}
	if (flag == 2)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

int	ft_exec_pipe(t_list *parse_list, t_parse *data, t_list *env)
{
    int		fork_id;
	int		fd[2];

	pipe(fd);
	fork_id = fork();
	if (fork_id == 0 && !parse_list->prev)
	{
        ft_set_dup(fd, 0);
		return (0);
	}
	else if(fork_id == 0)
	{
		ft_set_dup(fd, 1);
		return (0);
	}
	else if (fork_id == -1)
		return (-1);
	else
	{
		ft_set_dup(fd, 2);
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
	t_list	*tmp;
    t_list  *ret;
    t_parse	*parse;

    pipe_list = NULL;
    ret = NULL;
    if (line == NULL)
        return (ret);
    ft_list_pipe(line, &pipe_list);
	tmp = pipe_list;
    while (pipe_list)
    {
        parse = ft_parsing(pipe_list->content);
        ft_lst_add_content(parse, &ret, 2);
        pipe_list = pipe_list->next;
    }
    ft_free_list(tmp);
    return (ret);
}