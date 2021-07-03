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
	return (1);
}

/*	in questa funzione dobbiamo fare in modo che :
** 		[ ]	ciò che segue $ venga sostituito dall'elemento (di env) a cui $ si riferisce (se esiste);
**		[ ]	in caso l'elemento di riferimento a $ non esista, o $ non sia seguito da nulla,
**			la stringa di riferimento non venga scritta e il puntatore relativo non avanzi
**			alla stringa successiva di mtx.
**		[ ]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura (o omissione di scrittura) è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

int	ft_dollar(char *line, char **mtx, int *k, int *i)	
{
	return (1);
}

/*	in questa funzione dobbiamo fare in modo che :
**		[ ]	venga scritto il contenuto nelle <single_quotes>,
**			ivi compresi spazi, separatori, ecc;
**		[ ]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

int	ft_single_quote(char *line, char **mtx, int *k, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	*i++;
	while (line[*i + j] != '\'')
		j++;
	tmp = malloc(j + 1);
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, line + *i, j + 1);
	mtx[*k] = tmp;
	*k++;
	*i++;
	return (1);
}

/*	in questa funzione dobbiamo fare in modo che :
**		[ ]	venga scritto il contenuto nelle <double_quotes>,
**			ivi compresi spazi, separatori, ecc, FATTA ECCEZIONE per $;
**		[ ]	in caso di $ richiamare la funzione ft_dollar per sostituire
**			eventuale definizione (dove presente) nella stessa posizione
**			dove era $***;
**		[ ]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

int	ft_double_quote(char *line, char **mtx, int *k, int *i)
{
	return (1);
}

/*	in questa funzione dobbiamo fare in modo che :
**		[ ] la funzione esamini il char successivo della stringa (partendo da < o >)
**			e in caso di multipli < o >, scriverne fino a un max di 3 nella stringa
**			di riferimento in mtx.
**		[ ]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

int	ft_red(char *line, char **mtx, int *k, int *i)
{
	return (1);
}

/*	in questa funzione dobbiamo fare in modo che :
**		[ ]	qualsiasi altro caso rispetto ai precedenti venga gestito.
**		[ ]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

int	ft_else(char *line, char **mtx, int *k, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	while (line[*i + j] && !ft_is_in_str("\"\' <>", line[*i + j]))
	{
		if ()
		j++;
	}
	return (1);
}
