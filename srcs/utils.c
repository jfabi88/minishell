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

int	ft_n_flag(char **matrix)
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
		return (NULL);
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

int	ft_find_flag(char **stringa)
{
	int	i;

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
		printf("#: %s. No such file or directory\n", stringa);
	return (fd);
}
