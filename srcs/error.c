#include "minishell.h"

static void	ft_error_2(int nmb, char *str)
{
	if (nmb == 5)
	{
		printf("#: no such file or directory: %s\n", str);
		exit(0);
	}
}

static void	ft_error_1(int nmb, char *str)
{
	*str = *str;
	if (nmb == 1)
	{
		exit(0);
	}
}

void	ft_error(int nmb, char *str)
{
	if (nmb < 5)
		ft_error_1(nmb, str);
	if (nmb >= 5 && nmb < 10)
		ft_error_2(nmb, str);
}

void	ft_error_mat(char **mat, int nmb, char *str)
{
	ft_free_matrix(mat);
	if (nmb < 5)
		ft_error_1(nmb, str);
}