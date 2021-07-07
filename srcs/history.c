#include "minishell.h"

int	ft_cpy_history(t_list *list)
{
	int		fd;
	char	*dst;

	dst = ft_strjoin(ft_find_env(g_list_env, "HOME", 4), "/.minishell_history");
	if (dst == NULL)
		return (-1);
	fd = open(dst, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (fd);
	while (list)
	{
		ft_putstr_fd((char *)(list->content), fd);
		ft_putchar_fd('\n', fd);
		list = list->next;
	}
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
	if (num == 0)
		add_history(buffer);
	free(buffer);
	free(dst);
	return (num);
}
