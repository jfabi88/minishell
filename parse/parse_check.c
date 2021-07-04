#include "minishell.h"

static int	ft_check_red(char *line, char c)
{
	int	i;
	int	flag;

	i = 0;
	if (line[i] == c)
		i++;
	if (line[i] == c && c == '<')
		i++;
	while (line[i] == ' ')
		i++;
	flag = ft_is_in_str("\"#&\'()*\\;?`><", line[i]);
	if (flag == 1 && (line[i + 1] == ' ' || line[i + 1] == 0))
		return (ft_error(1, line[i], NULL));
	flag = ft_is_in_str("!#&()\\;`<>", line[i]);
	if (flag == 1 && (line[i + 1] != ' ' || line[i + 1] != 0))
		return (ft_error(1, line[i], NULL));
	flag = ft_is_in_str("./~", line[i]);
	if (flag == 1 && (line[i + 1] == ' ' || line[i + 1] == 0))
		return (ft_error(2, line[i], NULL));
	flag = ft_is_in_str("/~", line[i]);
	if (flag == 1 && (line[i + 1] != ' ' || line[i + 1] != 0))
		return (ft_error(2, line[i], NULL));
	if (line[i] == 0)
		return (ft_error(3, 0, NULL));
	return (1);
}

static int	ft_flag_check(char *str)
{
	int	num;

	num = 0;
	if ((str[0] == '<' || str[0] == '>'))
		num = ft_check_red(str + 1, str[0]);
	return (num);
}

int	ft_parse_check(char *line)
{
	int	i;
	int	flg;

	i = 0;
	flg = 0;
	while (line && line[i])
	{
		if (line[i] == '\'' && flg == 0 && ft_find_next_c(line, i, '\''))
			flg = 1;
		else if (line[i] == '\'' && flg == 1)
			flg = 0;
		else if (line[i] == '\"' && flg == 0 && ft_find_next_c(line, i, '\"'))
			flg = 2;
		else if (line[i] == '\"' && flg == 2)
			flg = 0;
		if (flg == 0 && ft_is_in_str("><", line[i]))
		{
			if (ft_flag_check(line + i) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}
