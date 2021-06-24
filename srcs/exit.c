#include "minishell.h"

int		ft_check_exit(char **stringa, t_parse *parse, char *line)
{
	int		fd;

	fd = ft_open_file(parse->output, 1);
	if (fd == -1)
		return (-1);
	if (fd != 1)
		close (fd);
	ft_free_listenv(list_env);
	ft_free_matrix(stringa);
	free(line);
	ft_free_parse(parse);
	ft_putstr_fd("exit\n", 1);
	exit(0);
}