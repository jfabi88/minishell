#include "minishell.h"

void	ft_run_extra_terminal(char *del)
{
	int		pid;
	int		status;
	char	*line;

	pid = fork();
	if (pid < 0)
		printf("qualcosa");                                  //si deve gestire l'errore
	else if (pid == 0)
	{
		line = readline("> ");
		while (line)
		{
			if (ft_strncmp(line, del, ft_strlen(del) + 1) == 0)
				exit(0);
			line = readline("> ");
		}
	}
	else
		wait(&status);
}

int	ft_open_file(char **output, int fd)
{
	int	i;
	int	flag;
	int	fd_2;

	i = 0;
	fd_2 = 0;
	while (output && output[i])
	{
		flag = ft_is_flag(output[i]);
		if (fd != 1 && (flag == 1 || flag == 3))
			close (fd);
		if (fd_2 != 0 && (flag == 2))
			close (fd_2);
		if (flag == 1 || flag == 3)
			fd = ft_open_arrow(flag, output[i + 1]);
		else if (flag == 2)
			fd_2 = ft_open_arrow(flag, output[i + 1]);
		else if (flag == 4)
			ft_run_extra_terminal(output[i + 1]);
		if (fd < 0 || fd_2 < 0)
			return (-1);
		i += 2;
	}
	return (fd);
}

int	ft_open_arrow(int flag, char *stringa)
{
	int	fd;

	if (flag == 1)
		fd = open(stringa, O_WRONLY | O_CREAT | O_TRUNC, 00755);
	else if (flag == 2)
		fd = open(stringa, O_RDONLY);
	if (flag == 3)
		fd = open(stringa, O_WRONLY | O_APPEND | O_CREAT, 00755);
	if (fd < 0)
	{
		ft_putstr_fd("#: ", 2);
		ft_putstr_fd(stringa, 2);
		ft_putstr_fd(". No such file or directory\n", 2);
	}
	return (fd);
}
