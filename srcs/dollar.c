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

int	ft_change_dollar(char *dst, char *src)
{
	int		len;
	char	*content;

	len = ft_find_next_str(src, " <>$");
	content = ft_find_env(list_env, src, len);
	len = ft_strlcpy(dst, content, ft_strlen(content) + 1);
	return (len);
}

int	ft_dollar_manager(char *line)// 26 lines
{
	int		i;
	int		j;
	int		flag;
	char	*tmp;
		
	i = 0;
	j = 0;
	tmp = malloc(ft_len_dollar(line) + 1);
	if (tmp == NULL)
		return (-1);
	flag = 1;
	while (line[i])
	{
		if (line[i] == '\'')
			flag *= -1;
		else if (line[i] == '$' && flag == 1)
		{
			j += ft_change_dollar(tmp + i, line + i + 1);
			i += ft_find_next_str(line + i + 1, " <>$") + 1;
		}
		else
			tmp[j++] = line[i++];
	}
	free (line);
	line = tmp;
	printf("line at the end of ft_dollar_manager : %s\n", line);//	<---------DEBUG
	return (1);
}
