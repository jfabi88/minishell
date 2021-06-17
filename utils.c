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

int		ft_n_flag(char **matrix)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], ">", 2) == 0)
			ret++;
		else if (ft_strncmp(matrix[i], "<", 2) == 0)
			ret++;
		else if (ft_strncmp(matrix[i], ">>", 3) == 0)
			ret++;
		else if (ft_strncmp(matrix[i], "<<", 3) == 0)
			ret++;
		i++;
	}
	return (ret);
}

char	*ft_convert_flag(int flag)
{
	char	*ret;

	if (flag == 1 || flag == 3 || flag == 5)
		ret = malloc(2);
	else if (flag == 2 || flag == 4)
		ret = malloc(3);
	else
		return (NULL);
	if (ret == 0)
		exit (0);
	if (flag == 1)
		ft_strlcpy(ret, ">", 2);
	if (flag == 2)
		ft_strlcpy(ret, ">>", 3);
	if (flag == 3)
		ft_strlcpy(ret, "<", 2);
	if (flag == 4)
		ft_strlcpy(ret, "<<", 3);
	if (flag == 5)
		ft_strlcpy(ret, "|", 2);
	return (ret);
}

char	**ft_create_strinput(char **mat)
{
	char	**ret;
	int		i;

	i = 1;
	ret = malloc(sizeof(char *) * (ft_mtrlen(mat) - (2 * ft_n_flag(mat)) + 1));
	if (ret == 0)
		exit (0);
	while (mat[i])
	{
		if (ft_is_flag(mat[i]) == 1)
			i++;
		else
		{
			ret[i] = malloc(sizeof(ft_strlen(mat[i] + 1)));
			if (ret[i] == 0)
			{
				ft_free_matrix(ret);
				exit (0);
			}
			ft_strlcpy(ret[i], mat[i], ft_strlen(mat[i]));
		}
		i++;
	}
	ret[i] = 0;
	i = 0;
	while (ret[i])
	{
		printf("%s\n", ret[i]);
		i++;
	}
	return (ret);
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
		if (ft_strncmp(stringa[i], "<<", 3) == 0)
			return (4);
		if (ft_strncmp(stringa[i], "|", 2) == 0)
			return (5);
		i++;
	}
	return (0);
}