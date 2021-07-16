#include "minishell.h"

static char	*ft_create_command(char *line, int *indx)
{
	//printf("Siamo dentro creare command\n");
	int		i;
	int		len;
	char	*ret;

	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] == '&' || line[i] == '|')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '(')
	{
		len = ft_next_pare(line + i) + 1;
		ret = ft_m_strlcpy(line + i + 1, len - 1);
	}
	else
	{
		len = ft_next_flag(line + i);
		//printf("Il valore di len: %d\n", len);
		ret = ft_m_strlcpy(line + i, len + 1); 
	}
	*indx += len + i;
	//printf("La grandezza é: %d\n", *indx);
	//printf("Siamo fuori creare command\n");
	return (ret);
}

static int	ft_create_commands(char *line, t_list **listone)
{
	//printf("Siamo dentro ft_create_commands\n");
	int		i;
	char	*tmp;
	t_list	*list;

	i = 0;
	list = 0;
	while (line[i])
	{
		tmp = ft_create_command(line + i, &i);
		if (tmp == NULL)
		{
			ft_lstdelone(*listone, free);
			return (-1);
		}
		list = ft_lstnew(tmp);
		if (list == NULL)
		{
			ft_lstdelone(*listone, free);
			return (-1);
		}
		//printf("Dobbiamo ancora aggiungere a lst->back\n");
		ft_lstadd_back(listone, list);
		//printf("Abbiamo aggiunto a lst back\n");
		while (line[i] == ' ')
			i++;
	}
	//printf("Siamo alla fine ft_create_commands\n");
	return (1);
}

int ft_list_token(char *line, t_token *token)
{
	//printf("Siamo dentro ft_list token\n");
	t_list	*list_string;
	t_list	*list_tmp;
	t_token	*tmp;
	int		num;

	//printf("Line: %s\n", line);
	list_string = NULL;
	num = ft_create_commands(line, &list_string);
	if (num == -1)
		return (-1);
	//printf("Fatto create commands\n");
	while(list_string)
	{
		tmp = ft_tokanizer(list_string->content);
		if (tmp == NULL)
		{
			ft_lstdelone(list_tmp, free);
			return (-1);
		}
		list_tmp = ft_lstnew(tmp);
		if (list_tmp == NULL)
		{
			ft_lstdelone(list_tmp, free);
			return (-1);
		}
		ft_lstadd_back(&token->commands, list_tmp);
		list_string = list_string->next;
	}
	return (1);
}