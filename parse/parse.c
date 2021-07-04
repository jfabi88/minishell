#include "minishell.h"

static int	ft_matlen_parse(char *line)
{
	int		len;
	int		i;
	int		flag_str;

	len = 0;
	i = 0;
	flag_str = 0;
	while (line[i])
	{
		flag_str = 0;
		if (ft_is_in_str("<> ", line[i]) && line[i + 1] != line[i])
			len++;
		else if (line[i] == '"' || line[i] == '\'')
		{
			i += ft_find_next_c(line, i, line[i]);
			flag_str = 1;
		}
		else
			flag_str = 1;
		i++;
	}
	return (len + flag_str);
}

char	**ft_parse_lst(char **line)
{
	int		len;
	char	*andr;
	char	**tmp;

	tmp = NULL;
	if (ft_parse_check(*line) == -1)
		return (NULL);
	andr = *line;
	*line = ft_dollar_manager(*line);
	free (andr);
	if (*line == NULL)
		return (NULL);
	len = ft_matlen_parse(*line);
	tmp = malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	if (ft_create_str_parse(tmp, *line) == -1)
	{
		ft_free_matrix(tmp);
		return (NULL);
	}
	return (tmp);
}
