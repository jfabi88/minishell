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

int	ft_find_flag(char **stringa)
{
	int i;

	i = 0;
	while (stringa[i])
	{
		if (ft_strncmp(stringa[i], ">", 2) == 0)
			return (1);
		if (ft_strncmp(stringa[i], ">>", 3) == 0)
			return (2);
		if (ft_strncmp(stringa[i], "<", 2) == 0)
			return (3);
		if (ft_strncmp(stringa[i], "|", 2) == 0)
			return (4);
		i++;
	}
	return (0);
}