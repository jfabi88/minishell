#include "minishell.h"

int	ft_len_file(char *dst)
{
	char	*buffer;
	int		fd;
	int		len;

	len = 0;
	fd = open(dst, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (ft_get_next_line(fd, &buffer) > 0)
	{
		len++;
		free(buffer);
	}
	if (buffer != NULL)
		free(buffer);
	close(fd);
	return (len);
}

int	ft_check_fdlist(char *dst, t_list **list)
{
	int		file_len;
	int		lst_len;
	t_list	*nw;

	nw = NULL;
	file_len = ft_len_file(dst);
	if (file_len == -1)
		return (-1);
	lst_len = ft_lstsize(*list);
	if (file_len + lst_len > 500)
	{
		if (ft_list_by_file(dst, &nw, file_len, file_len + lst_len - 500) == -1)
			return (-1);
		ft_lstadd_front(list, ft_lstlast(nw));
		*list = nw;
		return (1);
	}
	return (0);
}

int	ft_cpy_history(t_list *list)
{
	int		fd;
	int		flag;
	char	*dst;

	dst = ft_strjoin(ft_find_env(g_list_env, "HOME", 4), "/.minishell_history");
	if (dst == NULL)
		return (-1);
	flag = ft_check_fdlist(dst, &list);
	if (flag == 0)
		fd = open(dst, O_WRONLY | O_APPEND);
	else if (flag == 1)
		fd = open(dst, O_WRONLY | O_TRUNC);
	free (dst);
	if (flag >= 0 && fd == -1)
		return (-1);
	while (flag >= 0 && list)
	{
		ft_putstr_fd((char *)(list->content), fd);
		ft_putchar_fd('\n', fd);
		list = list->next;
	}
	if (flag >= 0)
		close (fd);
	return (1);
}

int	ft_change_history(char *line, t_list **list)
{
	t_list	*tmp;
	char	*cpy;

	add_history(line);
	cpy = malloc(ft_strlen(line) + 1);
	if (cpy == NULL)
		return (-1);
	ft_strlcpy(cpy, line, ft_strlen(line) + 1);
	tmp = ft_lstnew(cpy);
	if (tmp == NULL)
		return (-1);
	ft_lstadd_back(list, tmp);
	return (1);
}

int	ft_file_history(void)
{
	int		fd;
	int		num;
	char	*dst;
	char	*buffer;

	dst = ft_strjoin(ft_find_env(g_list_env, "HOME", 4), "/.minishell_history");
	if (dst == NULL)
		return (-1);
	fd = open(dst, O_RDONLY | O_CREAT, 00755);
	if (fd == -1)
		return (fd);
	num = ft_get_next_line(fd, &buffer);
	while (num == 1)
	{
		add_history(buffer);
		free(buffer);
		num = ft_get_next_line(fd, &buffer);
	}
	close (fd);
	free(buffer);
	free(dst);
	return (num);
}
