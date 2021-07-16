#include "minishell.h"

void	ft_print_token(t_token *token)
{
	static int	i;
	int			j;

	printf("La stringa del token %d é: %s\n", i, token->line);
	j = 0;
	while(token->flag)
	{
		printf("La flag numero %d del token %d é: %s\n", j, i, token->flag->content);
		j++;
		token->flag = token->flag->next;
	}
	i++;
	while (token->commands)
	{
		ft_print_token(token->commands->content);
		token->commands = token->commands->next;
	}
	i = 0;
}

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
	while (line[i])
	{
		if (!ft_is_in_quotes(line, i, '\'', '"'))
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
		if (line[i] == '(' && ft_is_in_quotes(line, i, '\'', '"' ) == 0)
			flag += 1;
		else if (line[i] == ')' && ft_is_in_quotes(line, i, '\'', '"' ) == 0)
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
		if (line[i] == '(' && ft_is_in_quotes(line, i, '\'', '"' ) == 0)
			flag += 1;
		else if (line[i] == ')' && ft_is_in_quotes(line, i, '\'', '"' ) == 0)
			flag += -1;
		if (flag == 0)
			return (i);
		if (flag == -1)
			return (-1);
		i++;
	}
	return (-2);
}
