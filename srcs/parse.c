#include "minishell.h"

static int	ft_matlen_parse(char *line)
{
	int		len;
	int		i;
	int		flag_str;

	len = 0;
	i = 0;
	flag_str = 0;
	while (line[i])
	{
		flag_str = 0;
		if (ft_is_in_str("<> ", line[i]) && line[i + 1] != line[i ])
			len++;
		else if (line[i] == '"' || line[i] == '\'')
		{
			i++;
			i += ft_find_next_c(line + i, line[i - 1]);
			flag_str = 1;
		}
		else
			flag_str = 1;
		i++;
	}
	return (len + flag_str);
}

int	ft_check_red(char *line, char c)
{
	int	i;

	i = 0;
	if (line[i] == c)
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_is_in_str("\"#&\'()*\\;?`", line[i]) == 0)
	{
		ft_putstr_fd("#: syntax error near unexpected token `", 2);
		ft_putchar_fd(line[i], 2);
		ft_putstr_fd("'\n", 2);
		return (-1);
	}
	else if (ft_is_in_str("./~", line[i]) == 0)
	{
		ft_putstr_fd("#: ", 2);
		ft_putchar_fd(line[i], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (-1);
	}
	return (1);
}


int	ft_flag_check(char *line)
{
	int	i;
	int	flg;

	i = 0;
	flg = 0;
	while (line && line[i])
	{
		if (line[i] == '"' && flg == 0)
			flg = 1;
		else if (line[i] == '"' && flg == 1)
			flg = 0;
		else if (line[i] == '\'' && flg != 1)
			flg = 2;
		else if (line[i] == '\'' && flg == 2)
			flg = 0;
		else if ((line[i] == '<' || line[i] == '>') && flg == 0)
			flg = ft_check_red(line + i, line[i]);
		i++;
	}
	return (1);
}

char	**ft_parse_lst(char *line)
{
	int	i;
	int	len;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (ft_flag_check(line) == -1)
		return (-1);
	len = ft_matlen_parse(line);
	printf("len : %d\n", len);
	// tmp = malloc(sizeof(char *))
	return (tmp);
}
/*	FLAGS DI INTERESSE :
**	[ ] $ : deve essere incluso nella stringa insieme a cio che  segue (si ferma agli spazi) (fino al prossimo flag);
**	[ ] <, >, <<, >> : devono essere inclusi singolarmente in nuova stringa della matrice;
**	[ ] spazio : non viene incluso mai nella stringa;
**	[ ] "", '' : vanno inclusi nella stringa tutti gli elementi all'interno delle quotes (quotes compresi).
**		la differenza tra i due tipi è che nel caso di "", il $ è gestito.
*/
