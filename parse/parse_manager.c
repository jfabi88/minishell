#include "minishell.h"

/*	ft_single_quote	:	in questa funzione dobbiamo fare in modo che :
**		[V]	venga scritto il contenuto nelle <single_quotes>,
**			ivi compresi spazi, separatori, ecc;
**		[V]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

static int	ft_single_quote(char *line, char **mtx, int *k, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	*i += 1;
	while (line[*i + j] != '\'')
		j++;
	tmp = malloc(j + 1);
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, line + *i, j + 1);
	mtx[*k] = tmp;
	*k += 1;
	*i += j + 1;
	//printf("line at the end of ft_single_quote : %s\n", mtx[*k - 1]);//	<---------DEBUG
	if (line[*i] == 0)
		return (0);
	return (1);
}

/*	ft_double_quote	:	in questa funzione dobbiamo fare in modo che :
**		[ ]	venga scritto il contenuto nelle <double_quotes>,
**			ivi compresi spazi, separatori, ecc, *FATTA ECCEZIONE PER $;
**		[V]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
**
**		*	viene gestito in fase di check (ft_parse_lst/ft_dollar_manager) e sostituito
**			in ft_change_dollar.
*/

static int	ft_double_quote(char *line, char **mtx, int *k, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	*i += 1;
	while (line[*i + j] != '\"')
		j++;
	tmp = malloc(j + 1);
	if (tmp == NULL)
		return (-1);
	ft_strlcpy(tmp, line + *i, j + 1);
	mtx[*k] = tmp;
	*k += 1;
	*i += j + 1;
	//printf("line at the end of ft_double_quote : %s\n", mtx[*k - 1]);//	<---------DEBUG
	if (line[*i] == 0)
		return (0);
	return (1);
}

/*	ft_red : in questa funzione dobbiamo fare in modo che :
**		[V] la funzione esamini il char successivo della stringa (partendo da < o >)
**			e in caso di multipli < o >, scriverne fino a un max di (3 se <; 2 se <)
**			nella stringa di riferimento in mtx.
**		[V]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
**	COMPORTAMENTO DI <<<:	se trova riscontro con valore a sx nell'elemento a dx,
**							lo stampa a video, altrimenti "bash: <elm_sx>: command not found";
**	COMPORTAMENTO DI << :	apre quote, in attesa di ricevere in input elemento dx. Quando
**							questo avviene, si chiude quote e stampa valore sx;
**	COMPORTAMENTO DI >> :	crea un file con nome elemento dx (se non esiste) e scrive
**							al suo interno il valore sx (appended);
**	COMPORTAMENTO DI >	:	crea un file con nome elemento dx (se non esiste) e scrive
**							al suo interno il valore sx, sovrascrivendone i precedenti valori.
*/

static int	ft_red(char *line, char **mtx, int *k, int *i)//	27 lines
{
	char	*tmp;
	int		j;

	j = 0;
	while (line[*i + j] == line[*i])
		j++;
	tmp = malloc(j + 1);
	if (tmp == NULL)
		return (-1);
	ft_strlcpy(tmp, line + *i, j + 1);
	mtx[*k] = tmp;
	*k += 1;
	*i += j;
	//printf("line at the end of ft_red : |%s|\n", mtx[*k - 1]);//	<---------DEBUG
	if (line[*i] == 0)
		return (0);
	return (1);
}

/*	ft_else	: in questa funzione dobbiamo fare in modo che :
**		[V]	qualsiasi caso standard in cui va copiato tutto fino al prossimo separatore;
**		[V]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

static int	ft_else(char *line, char **mtx, int *k, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	while (line[*i + j] && !ft_is_in_str(" <>", line[*i + j]))
		j++;
	tmp = malloc(j + 1);
	if (tmp == NULL)
		return (-1);
	ft_strlcpy(tmp, line + *i, j + 1);
	mtx[*k] = tmp;
	*k += 1;
	*i += j;
	//printf("line at the end of ft_else : |%s|\n", mtx[*k - 1]);
	if (line[*i] == 0)
		return (0);
	return (1);
}

int	ft_create_str_parse(char **mtx, char *line)
{
	int	i;
	int	k;
	int num;

	i = 0;
	k = 0;
	num = 0;
	while (line[i])
	{
		if (line[i] == '\'' && ft_find_next_c(line, i, line[i]))
			num = ft_single_quote(line, mtx, &k, &i);
		else if (line[i] == '\"' && ft_find_next_c(line, i, line[i]))
			num = ft_double_quote(line, mtx, &k, &i);
		else if (line[i] == '>' || line[i] == '<')
			num = ft_red(line, mtx, &k, &i);
		else if (line[i] != ' ')
			num = ft_else(line, mtx, &k, &i);
		else
			i++;
		if (num == -1)
			return (num);
	}
	mtx[k] = 0;
	return (1);
}
