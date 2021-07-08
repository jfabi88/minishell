#include "minishell.h"

int	ft_execute_command(t_parse *parse)
{
	int		pid;
	char	**mtx;

	pid = fork();
	if (pid == 0)
	{
		mtx = ft_lst_to_mtx(g_list_env);
		if (mtx == NULL)
			exit (-1);
		int i = 0;
		while (mtx[i])
		{
			printf("%s\n", mtx[i]);
			i++;
		}
		printf("%s\n", parse->command);
		if (execve(parse->command, parse->input, mtx) == -1)
			exit (-1);
		ft_free_matrix(mtx);
		_exit (1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (1);
	}
}
