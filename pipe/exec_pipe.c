#include "minishell.h"

static int	ft_exec_pipe_father(int fd[2], t_parse *data)
{
	int	fd_red[2];

	close(fd[1]);
	ft_open_red(data->output, &fd_red[0], &fd_red[1]);
	if (fd_red[0] == 0)
		dup2(fd[0], STDIN_FILENO);
	else
	{
		dup2(fd_red[0], STDIN_FILENO);
		close(fd_red[0]);
	}
	close(fd[0]);
	dup2(fd_red[1], STDOUT_FILENO);
	return (1);
}

static int	ft_exec_pipe_child(int fd[2], t_parse *data, t_list *h, t_list *env)
{
	int	fd_red[2];

	close(fd[0]);
	if (ft_open_red(data->output, &fd_red[0], &fd_red[1]) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		return (1);
	}
	if (fd_red[1] == 1)
		dup2(fd[1], STDOUT_FILENO);
	else
	{
		dup2(fd_red[1], STDOUT_FILENO);
		close(fd_red[1]);
	}
	close(fd[1]);
	dup2(fd_red[0], STDIN_FILENO);
	return (ft_execute(data, h, env));
}

int	ft_exec_pipe(t_parse *data, t_parse *d_next, t_list *history, t_list *env)
{
	int	fork_id;
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	fork_id = fork();
	if (fork_id < 0)
		return (-1);
	else if (fork_id == 0)
		exit (ft_exec_pipe_child(fd, data, history, env));
	else
	{
		waitpid(fork_id, NULL, 0);
		ft_exec_pipe_father(fd, d_next);
		return (1);
	}
}
