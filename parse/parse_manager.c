#include "minishell.h"

static size_t	ft_strlcpy_no_c(char *dst, char *s, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == 0 || dst == 0)
		return (0);
	if (size != 0)
	{
		while (i < (size - 1) && s[i] != 0)
		{
			if (s[i] == '\'' && ft_is_quotes(s, i, '\'', '"') != 1)
				dst[j++] = s[i];
			else if (s[i] == '"' && ft_is_quotes(s, i, '"', '\'') != 1)
				dst[j++] = s[i];
			else if (s[i] != '\'' && s[i] != '"')
				dst[j++] = s[i];
			i++;
		}
		dst[j] = 0;
	}
	return (j);
}

static int	ft_red(char *line, char **mtx, int k)//	27 lines
{
	char	*tmp;
	int		j;

	j = 0;
	while (line[j] == line[0])
		j++;
	tmp = malloc(j + 1);
	if (tmp == NULL)
		return (-1);
	ft_strlcpy(tmp, line, j + 1);
	mtx[k] = tmp;
	//printf("line at the end of ft_red : |%s|\n", mtx[*k - 1]);//	<---------DEBUG
	return (j);
}

static int	ft_cpy(char *l, char **mtx, int k)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (l[i] && (!ft_is_in_str(" <>", l[i]) || ft_is_in_quotes(l, i, '\'', '\"')))
	{
		if (l[i] == '\'' && ft_is_quotes(l, i , '\'', '\"') == 1)
			j += 0;
		if (l[i] == '"' && ft_is_quotes(l, i , '"', '\'') == 1)
			j += 0;
		else
			j++;
		i++;
	}
	mtx[k] = malloc(j + 1);
	if (mtx[k] == NULL)
		return (-1);
	ft_strlcpy_no_c(mtx[k], l, i + 1);
	return (i);
}

int	ft_create_str_parse(char **mtx, char *line)//	la condizione di stampa $ dentro a <single_quotes>, comprese in <double_quotes> va inserita qui!
{
	int	i;
	int	k;
	int	num;

	i = 0;
	k = 0;
	while (line[i])
	{
		num = 0;
		if (line[i] == ' ')
			i++;
		else
		{
			if ((line[i] == '>' || line[i] == '<'))
				num = ft_red(line + i, mtx, k);
			else
				num = ft_cpy(line + i, mtx, k);
			if (num == -1)
				return (num);
			i += num;
			k++;
		}
	}
	mtx[k] = 0;
	return (1);
}
