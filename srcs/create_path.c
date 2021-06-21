#include "minishell.h"

char	*ft_add_path(char *start, char *add)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin("/", add);
	if (temp == NULL)
		return (NULL);
	path = ft_strjoin(start, temp);
	if (path == NULL)
		return (NULL);
	free(temp);
	return (path);
}

char	*ft_sub_path(char *start)
{
	char	*temp;
	char	*path;
	int		len1;
	int		len2;

	temp = ft_strrchr(start, '/');
	len1 = ft_strlen(temp);
	len2 = ft_strlen(start) - len1;
	path = malloc(len2 + 1);
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, start, len2 + 1);
	return (path);
}

char	*ft_create_path(t_list *list, char *str)
{
	char	*temp;
	char	*path;
	char	**matrix;
	int		i;

	i = 0;
	temp = ft_find_env(list, "PWD");
	matrix = ft_split(str, '/');
	path = malloc(ft_strlen(temp) + 1);
	if (path == NULL || matrix == NULL)
		return (NULL);
	ft_strlcpy(path, temp, ft_strlen(temp) + 1);
	while (matrix && matrix[i])
	{
		temp = path;
		if (ft_strncmp(matrix[i], "..", 3) == 0)
			path = ft_sub_path(path);
		else
			path = ft_add_path(path, matrix[i]);
		free(temp);
		i++;
	}
	return (path);
}

char	*ft_create_home_path(t_list *list)
{
	int		len;
	char	*path;

	len = ft_strlen(ft_find_env(list, "HOME"));
	path = malloc(len + 1);
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, ft_find_env(list, "HOME"), len + 1);
	return (path);
}