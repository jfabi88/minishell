#include "minishell.h"

void	*ft_free_null(void	*obj)
{
	free(obj);
	return (NULL);
}

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

int	ft_find_next_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
