#include "minishell.h"

int	ft_len_dollar(char *line)
{
	int		flag;
	int		i;
	int		len;
	int		tot;

	i = 0;
	len = 0;
	tot = 0;
	flag = 1;
	while (line[i])
	{
		if (line[i] == '\'')
			flag *= -1;
		else if (line[i] == '$' && flag == 1)
		{
			len = ft_find_next_str(line + i + 1, " <>$");
			tot += ft_strlen(ft_find_env(list_env, line + i, len));
			i += len;
		}
		else
			tot++;
		i++;
	}
	return (tot);
}

int	ft_change_dollar(char *dst, char *src, int src_pos)
{
	int		len;
	char	*content;

	if (ft_between_c(src, src_pos, '"'))
		len = ft_find_next_str(src + src_pos + 1, " \"<>$");
	else
		len = ft_find_next_str(src + src_pos + 1, " <>$");
	content = ft_find_env(list_env, src + src_pos + 1, len);
	ft_memcpy(dst, content, ft_strlen(content));
	return (ft_strlen(content));
}

char	*ft_dollar_manager(char *line)// 26 lines
{
	int		i;
	int		j;
	char	*tmp;
		
	i = 0;
	j = 0;
	tmp = malloc(ft_len_dollar(line) + 1);
	if (tmp == NULL)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && ft_between_c(line, i, '\'') == 0)
		{
			j += ft_change_dollar(tmp + j, line, i);
			if (ft_between_c(line, i, '\"'))
				i += ft_find_next_str(line + i + 1, " \"<>$") + 1;
			else
				i += ft_find_next_str(line + i + 1, " <>$") + 1;
		}
		else
			tmp[j++] = line[i++];
	}
	tmp[j] = 0;
	return (tmp);
	printf("line at the end of ft_dollar_manager : %s\n", tmp);//	<---------DEBUG
}
