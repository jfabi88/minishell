#include "minishell.h"

int		ft_check_exit(char **stringa, char *line)
{
	char	**output;
	int		fd;

	output = ft_create_stroutput(stringa);
	if (output == NULL)
		return (-1);
	fd = ft_open_file(output, 1);
	if (fd == -1)
		return (-1);
	if (fd != 1)
		close (fd);
	ft_free_listenv(list_env);
	ft_free_matrix(output);
	ft_free_matrix(stringa);
	free(line);
	ft_putstr_fd("exit\n", 1);
	exit(0);
}