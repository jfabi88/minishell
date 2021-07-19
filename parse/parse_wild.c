#include "minishell.h"

char	*ft_take_str(char *line, int pos)
{
	int		i;
	char	*ret;

	while (pos > 0 && !ft_is_in_str("<> \'\"", line[pos - 1]))
		pos--;
	i = pos;
	while (!ft_is_in_str("<> \'\"", line[i]))
		i++;
	ret = ft_m_strlcpy(line + pos, i + 1);
	if (ret == NULL)
		return (NULL);
	return (ret);	
}

int	ft_len_wild(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		if (line[i] == '*' && !ft_is_in_quotes(line, i, '\'', '\"'))
		{
			tmp = ft_take_str(line, i);
			if (tmp == NULL)
				return (-1);
			
		}
	}
}

char	*ft_wild_card(char *line, t_list *var)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '*' && !ft_is_in_quotes(line, i, '\'', '\"'))
		{

		}
	}
}