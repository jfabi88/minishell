#include "minishell.h"

static char	**ft_create_strinput(char **mat)
{
	char	**ret;
	int		i;
	int		j;

	i = 1;
	j = 0;
	ret = malloc(sizeof(char *) * (ft_mtrlen(mat) - (2 * ft_n_flag(mat))));
	if (ret == 0)
		return (NULL);
	while (mat[i])
	{
		if (ft_is_flag(mat[i]) == 0 && ft_is_flag(mat[i - 1]) == 0)
		{
			ret[j] = malloc(ft_strlen(mat[i]) + 1);
			if (ret[j] == 0)
			{
				ft_free_matrix(ret);
				return (NULL);
			}
			ft_strlcpy(ret[j++], mat[i], ft_strlen(mat[i]) + 1);
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}

static char	**ft_create_stroutput(char **mat)					//jfabi c'è un probabile errore con la redirectiori << perche penso prenda come argomento ciò che ha subito dopo
{
	char	**ret;
	int		i;
	int		j;

	i = 1;
	j = 0;
	ret = malloc(sizeof(char *) * (2 * ft_n_flag(mat) + 1));
	if (ret == 0)
		return (NULL);
	while (mat[i])
	{
		if (ft_is_flag(mat[i]) != 0 || ft_is_flag(mat[i - 1]) != 0)
		{
			ret[j] = malloc(ft_strlen(mat[i]) + 1);
			if (ret[j] == 0)
			{
				ft_free_matrix(ret);
				return (NULL);
			}
			ft_strlcpy(ret[j++], mat[i], ft_strlen(mat[i]) + 1);
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}

t_parse	*ft_create_parse(char **stringa)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse *));
	if (parse == NULL)
		return (NULL);
	parse->command = ft_strdup(stringa[0]);
	if (parse->command == NULL)
		return (ft_free_null(parse));
	parse->input = ft_create_strinput(stringa);
	if (parse->input == NULL)
	{
		free(parse->command);
		free(parse);
		return (NULL);
	}
	parse->output = ft_create_stroutput(stringa);
	if (parse->output == NULL)
	{
		free(parse->command);
		free(parse->input);
		free(parse);
		return (NULL);
	}
	return (parse);
}

void	ft_free_parse(t_parse *parse)
{
	free(parse->command);
	ft_free_matrix(parse->input);
	ft_free_matrix(parse->output);
	free(parse);
}
