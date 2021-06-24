#include "minishell.h"

int	ft_find_strposition(char *str, char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], str, ft_strlen(str) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}
