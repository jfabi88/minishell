#include "minishell.h"

static int	ft_check_par(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 0)
		return (ft_error(10, 0, "newline"));
	else if (line[i] == '&' && line[i + 1] == '&')
		return (ft_error(10, 0, "&&"));
	else if (line[i] == '&')
		return (ft_error(10, 0, "&"));
	else if (line[i] == '|' && line[i + 1] == '|')
		return (ft_error(10, 0, "||"));
	else if (line[i] == '|')
		return (ft_error(10, 0, "|"));
	else if (line[i] == ')')
		return (ft_error(10, 0, ")"));
	return (1);
}

static int	ft_first_car(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 0)
		return (-1);
	if (line[i] == '&' && line[i + 1] == '&')
		return (ft_error(10, 0, "&&"));
	else if (line[i] == '&')
		return (ft_error(10, 0, "&"));
	else if (line[i] == '|' && line[i + 1] == '|')
		return (ft_error(10, 0, "||"));
	else if (line[i] == '|')
		return (ft_error(10, 0, "|"));
	else if (line[i] == ')')
		return (ft_error(10, 0, ")"));
	return (1);
}

static int	ft_check_ao(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i + j] == line[i] && j < 2)
		j++;
	return (ft_first_car(line + i + j));
}

int	ft_check_token(char *ln)
{
	int	i;
	int	num;

	i = 0;
	while (ln && ln[i])
	{
		num = 0;
		if (i == 0 && ln[i] != '(')
			num = ft_first_car(ln);
		else if (ln[i] == '(')
		{
			num = ft_check_par(ln + i + 1);
			if (num != -1)
			{
				if (ft_next_pare(ln + i) == -2)
					return (ft_error(10, 0, "("));
			}
		}
		else if ((ln[i] == '&' && ln[i + 1] == '&') || ln[i] == '|')
			num = ft_check_ao(ln + i);
		if (num == -1)
			return (-1);
		i++;
	}
	return ((ln != NULL) - 1);
}
