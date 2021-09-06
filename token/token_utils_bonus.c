#include "minishell.h"

void	ft_print_token(t_token *token)
{
	t_list		*s_flag;
	t_list		*s_commands;
	t_list		*flag;
	t_list		*commands;
	static int	i;
	int			j;

	s_flag = token->s_flag;
	s_commands = token->s_commands;
	flag = token->flag;
	commands = token->commands;
	printf("La stringa del token %d é: %s\n", i, token->line);
	j = 0;
	while (s_flag)
	{
		printf("La flag paritaria numero %d del token %d é: %s\n", j, i, s_flag->content);
		j++;
		s_flag = s_flag->next;
	}
	while (s_commands)
	{
		ft_print_token(s_commands->content);
		s_commands = s_commands->next;
	}
	while(flag)
	{
		printf("La flag numero %d del token %d é: %s\n", j, i, flag->content);
		j++;
		flag = flag->next;
	}
	i++;
	while (commands)
	{
		ft_print_token(commands->content);
		commands = commands->next;
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
