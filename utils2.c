#include "minishell.h"

int	ft_is_flag(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (3);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (4);
	return (0);
}

char	**ft_create_strinput(char **mat)
{
	char	**ret;
	int		i;
	int		j;

	i = 1;
	j = 0;
	ret = malloc(sizeof(char *) * (ft_mtrlen(mat) - (2 * ft_n_flag(mat))));
	if (ret == 0)
		ft_error(1, NULL);
	while (mat[i])
	{
		if (ft_is_flag(mat[i]) == 0 && ft_is_flag(mat[i - 1]) == 0)
		{
			ret[j] = malloc(sizeof(ft_strlen(mat[i]) + 1));
			if (ret[j] == 0)
				ft_error_mat(ret, 1, NULL);
			ft_strlcpy(ret[j], mat[i], ft_strlen(mat[i]) + 1);
			j++;
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}

char	**ft_create_stroutput(char **mat)
{
	char	**ret;
	int		i;
	int		j;

	i = 1;
	j = 0;
	ret = malloc(sizeof(char *) * (2 * ft_n_flag(mat) + 1));
	if (ret == 0)
		ft_error(1, NULL);
	while (mat[i])
	{
		if (ft_is_flag(mat[i]) != 0 || ft_is_flag(mat[i - 1]) != 0)
		{
			ret[j] = malloc(sizeof(ft_strlen(mat[i]) + 1));
			if (ret[j] == 0)
				ft_error_mat(ret, 1, NULL);
			ft_strlcpy(ret[j], mat[i], ft_strlen(mat[i]) + 1);
			j++;
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}