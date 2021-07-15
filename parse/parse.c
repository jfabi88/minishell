#include "minishell.h"

static int	ft_redlen_parse(char *line)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (ft_is_in_str("<>", line[i]) && line[i + 1] != line[i])
		{
			if (!ft_is_in_quotes(line, i, '\'', '"'))
				len++;
		}
		i++;
	}
	return (len * 2);
}

static int	ft_matlen_parse(char *line)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i += ft_find_next_c(line, i, line[i]);
		else if (ft_is_in_str("<>", line[i]))
		{
			if (i != 0 && (line[i - 1] != line[i]))
				len++;
			if (line[i + 1] != line[i] && line[i + 1] != ' ')
				len++;
		}
		else if (line[i] == ' ' && !ft_is_in_str("<> ", line[i + 1]))
			len++;
		i++;
	}
	if (i != 0 && !ft_is_in_str("<> ", line[i - 1]))
		return (len + 1);
	return (len);
}

static int	ft_parse_lst(char **line, t_parse *parse)
{
	int		len;
	int		r_len;

	if (ft_parse_check(*line) == -1)
		return (-1);
	len = ft_matlen_parse(*line);
	r_len = ft_redlen_parse(*line);
	printf("Le due grandezzr sono: %d e %d\n", len, r_len);
	parse->input = (char **)ft_calloc(sizeof(char *), (len - r_len + 1));
	if (parse->input == NULL)
		return (-1);
	parse->output = (char **)ft_calloc(sizeof(char *), (r_len + 1));
	if (parse->output == NULL)
	{
		free(parse->input);	
		return (-1);
	}
	if (ft_create_str_parse(parse->input, parse->output, *line) == -1)
	{
		ft_free_matrix(parse->input);
		ft_free_matrix(parse->output);
		return (-1);
	}
	return (1);
}

t_parse	*ft_parsing(char **line)
{
	t_parse	*parse;
	char	*tmp;

	tmp = *line;
	*line = ft_dollar_manager(*line);
	free (tmp);
	if (*line == NULL)
		return (NULL);
	if (ft_parse_check(*line) == -1)
		return (NULL);
	parse = (t_parse *)malloc(sizeof(t_parse));
	if (parse == NULL)
		return (NULL);
	if (ft_parse_lst(line, parse) == -1)
		return(ft_free_null(parse));
	parse->command = ft_m_strlcpy(parse->input[0], ft_strlen(parse->input[0]) + 1);
	if (parse->command == NULL)
	{
		ft_free_matrix(parse->input);
		ft_free_matrix(parse->output);
		return (NULL);
	}
	return (parse);
}
