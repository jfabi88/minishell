#include "minishell.h"

static int	ft_matlen_parse(char *line)
{
	int			len;
	int			i;
	int			flag_str;
	const char	flag[4];

	len = 0;
	i = 0;
	flag = ">< ";// <-----------YOU ARE HERE!
	flag_str = 0;
	while (line[i])
	{
		flag_str = 0;
		if (ft_is_in_str(flag, line[i]) && line[i + 1] != line[i ])
			len++;
		else if (line[i++] == '"' || line[i++] == '\'')
		{
			i += ft_find_next_c(line + i, line[i - 1]);
			flag_str = 1;
		}
		else
			flag_str = 1;
		i++;
	}
	return (len + flag_str);
}

char	**ft_parse_lst(char *line)
{
	int	i;
	int	len;
	char	**tmp;

	i = 0;
	tmp = NULL;
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
