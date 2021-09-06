#include "minishell.h"

void	ft_free_parse(t_parse *parse)
{
	free(parse->command);
	ft_free_matrix(parse->input);
	ft_free_matrix(parse->output);
	free(parse);
}

int	ft_is_quotes(char *str, int c_pos, char c, char d)
{
	if (ft_in_quotes(str, c_pos + 1, c, d) == 1)
		return (1);
	if (c_pos != 0 && ft_in_quotes(str, c_pos - 1, c, d) == 1)
		return (1);
	if (str[c_pos] == str[c_pos + 1])
		return (1);
	if (c_pos != 0 && str[c_pos] == str[c_pos - 1])
		return (1);
	return (0);
}

int	ft_in_quotes(char *str, int c_pos, char c, char d)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < c_pos)
	{
		if (str[i] == c && flag == 0)
			flag = 1;
		else if (str[i] == c && flag == 1)
			flag = 0;
		else if (str[i] == d && flag == 0)
			flag = 2;
		else if (str[i] == d && flag == 2)
			flag = 0;
		i++;
	}
	if (flag == 0)
		return (0);
	if (flag == 2 && ft_find_next_c(str, i, d))
		return (2);
	else if (flag == 1 && ft_find_next_c(str, i, c))
		return (1);
	return (0);
}
