#include "minishell.h"

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

int	ft_create_token(char *line, t_list **list)
{
	int		i;
	int		add;

	i = 0;
	while (line && line[i])
	{
		add = 1;
		if ((line[i] == '&' || line[i] == '|'))
		{
			if (!ft_is_inpar(line, i) && !ft_in_quotes(line, i, '\'', '"'))
			{
				add = ft_add_t_flag(list, line + i);
				if (add == -1)
					return (-1);
			}
		}
		i += add;
	}
	return (1);
}

int	ft_par(char *line, t_token **token)
{
	int		len;
	char	*ret;

	len = ft_next_flag(line);
	ret = ft_m_strlcpy(line, len + 1);
	if (ret == NULL)
		return (-1);
	(*token)->line = ret;
	(*token)->s_flag = NULL;
	if (ft_create_token(line + len, &((*token)->s_flag)) == -1)
	{
		free((*token)->line);
		return (-1);
	}
	(*token)->s_commands = NULL;
	len += ft_after_flag(line + len);
	if (ft_list_token(line + len, (&(*token)->s_commands)) == -1)
	{
		free((*token)->line);
		ft_lstdelone((*token)->s_flag, free);
		return (-1);
	}
	return (1);
}

int	ft_del_par(char *line, t_token **token)
{
	int		i;
	int		len;
	char	*ret;

	i = ft_count_c(line, ' ');
	len = 0;
	ret = NULL;
	if (line && line[i] == '(')
	{
		len = ft_next_pare(line + i) + 1;
		ret = ft_m_strlcpy(line + i + 1, len - 1);
	}
	else if (line && line[i])
	{
		len = ft_next_flag(line + i);
		ret = ft_m_strlcpy(line + i, len + 1);
	}
	if (line && ret == NULL)
		return (-1);
	if (line)
		ft_par(ret, token);
	free(ret);
	if (line && (*token)->line == NULL)
		return (-1);
	return (i + len);
}

t_token	*ft_tokanizer(char *line)
{
	t_token	*ret;
	char	*tmp;
	int		len;

	if (ft_check_token(line) == -1)
		return (NULL);
	ret = ft_init_token();
	if (ret == NULL)
		return (NULL);
	len = ft_del_par(line, &ret);
	if (len == -1)
		return (ft_free_null(ret));
	if (ft_create_token(line + len, &ret->flag) == -1)
	{
		ft_free_token(ret);
		return (NULL);
	}
	len += ft_after_flag(line + len);
	if (ft_list_token(line + len, &ret->commands) == -1)
	{
		ft_free_token(ret);
		return (NULL);
	}
	return (ret);
}
