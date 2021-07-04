#include "minishell.h"

int	ft_between_c(char *str, int c_pos, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < c_pos)
	{
		if (str[i] == c && flag == 0)
			flag = 1;
		else if (str[i] == c && flag == 1)
			flag = 0;
		i++;
	}
	if (flag == 0)
		return (0);
	if (ft_find_next_c(str + i, c))
		return (1);
	return (0);
}

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

	i = 1;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == 0)
		return (0);
	return (i);
}

int	ft_find_next_str(char *str, const char *ref)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_in_str(ref, str[i]) == 0)
		i++;
	return (i);
}

int	ft_is_in_str(const char *str, char c)
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
