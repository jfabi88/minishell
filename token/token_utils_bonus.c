#include "minishell.h"

int	ft_after_flag(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] == ' ')
		i++;
	while (line && (line[i] == '|' || line[i] == '&'))
		i++;
	return (i);
}

int	ft_next_flag(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_in_quotes(line, i, '\'', '"'))
		{
			if (line[i] == '|' || !ft_strncmp("&&", line + i, 2))
				return (i);
			else if (!ft_strncmp("||", line + i, 2))
				return (i);
		}
		i++;
	}
	return (i);
}

int	ft_is_inpar(char *line, int pos)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < pos)
	{
		if (line[i] == '(' && ft_in_quotes(line, i, '\'', '"' ) == 0)
			flag += 1;
		else if (line[i] == ')' && ft_in_quotes(line, i, '\'', '"' ) == 0)
			flag += -1;
		i++;
	}
	return (flag);
}

int	ft_next_pare(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '(' && ft_in_quotes(line, i, '\'', '"' ) == 0)
			flag += 1;
		else if (line[i] == ')' && ft_in_quotes(line, i, '\'', '"' ) == 0)
			flag += -1;
		if (flag == 0)
			return (i);
		if (flag == -1)
			return (-1);
		i++;
	}
	return (-2);
}
