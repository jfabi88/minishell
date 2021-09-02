#include "minishell.h"

void    ft_save_fd(int *fd_in, int *fd_out)
{
    *fd_in = dup(STDIN_FILENO);
	*fd_out = dup(STDOUT_FILENO);
}

void    ft_restore_fd(int fd[2])
{
    dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}