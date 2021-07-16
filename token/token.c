#include "minishell.h"

int	ft_del_par(char *line, t_token *token)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '(')
	{
		len = ft_next_pare(line + i) + 1;
		ret = ft_m_strlcpy(line + i + 1, len - 1);
	}
	else
	{
		len = ft_next_flag(line + i);
		ret = ft_m_strlcpy(line + i, len + 1); 
	}
	if (ret == NULL)
		return (-1);
	token->line = ret;
	//printf("La stringa é: %s\n", token->line);
	return (i + len);
}

int	ft_add_t_flag(t_list **list, char *line)
{
	int		i;
	char	*str;
	t_list	*tmp;

	i = 0;
	while (line[i] == line[0])
		i++;
	str = ft_m_strlcpy(line, i + 1);
	if (str == NULL)
	{
		ft_lstdelone(*list, free);
		return (-1);
	}
	tmp = ft_lstnew(str);
	if (tmp == NULL)
	{
		ft_lstdelone(*list, free);
		return (-1);
	}
	ft_lstadd_back(list, tmp);
	return (i);
}

int	ft_create_token(char *line, t_token *token)
{
	int		i;
	int		add;
	
	i = 0;
	while (line && line[i])
	{
		add = 1;
		if ((line[i] == '&' || line[i] == '|'))
		{
			if (!ft_is_inpar(line, i) && !ft_is_in_quotes(line, i, '\'', '"'))
			{
				add = ft_add_t_flag(&token->flag, line + i);
				if (add == -1)
					return (-1);
			}
		}
		i += add;
	}
	return (1);
}

t_token	*ft_tokanizer(char *line)
{
	t_token	*ret;
	char	*tmp;
	int		len;

	ret = (t_token *)malloc(sizeof(t_token));
	if (ret == NULL)
		return (NULL);
	len = ft_del_par(line, ret);
	//printf("il valore di len é: %d\n", len);
	//printf("La stringa fuori é: %s\n", ret->line);
	if (len == -1)
		return (ft_free_null(ret));
	ret->flag = NULL;
	if (ft_create_token(line + len, ret) == -1)
	{
		free(ret->line);
		free(ret);
		return (NULL);
	}
	ret->commands = NULL;
	len += ft_after_flag(line + len);
	if (ft_list_token(line + len, ret) == -1)
	{
		free(ret->line);
		ft_lstdelone(ret->flag, free);
		free(ret);
		return (NULL);
	}
	return (ret);
}