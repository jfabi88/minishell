#include "minishell.h"

/*	ft_dollar	:	in questa funzione (SE NECESSARIA) dobbiamo fare in modo che :
** 		[ ]	ciò che segue $ venga sostituito dall'elemento (di env) a cui $ si riferisce (se esiste);
**		[ ]	in caso l'elemento di riferimento a $ non esista, o $ non sia seguito da nulla,
**			la stringa di riferimento non venga scritta e il puntatore relativo non avanzi
**			alla stringa successiva di mtx.
**		[ ]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura (o omissione di scrittura) è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

// int	ft_dollar(char *line, char **mtx, int *k, int *i)// forse questa non serve più... (ft_else?)	
// {
// 	return (1);
// }

/*	ft_single_quote	:	in questa funzione dobbiamo fare in modo che :
**		[V]	venga scritto il contenuto nelle <single_quotes>,
**			ivi compresi spazi, separatori, ecc;
**		[V]	alla fine la funzione restituisca:
**			a.	1 se il processo di scrittura è andato a buon fine;
**			b.	-1 se è intercorso un errore;
**			c.	0 se la lettura della stringa in ingresso è arrivata a EOS.
*/

int	ft_single_quote(char *line, char **mtx, int *k, int *i)
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
	printf("line at the end of ft_single_quote : %s\n", line);//	<---------DEBUG
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

int	ft_double_quote(char *line, char **mtx, int *k, int *i)
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
	printf("line at the end of ft_double_quote : %s\n", mtx[*k - 1]);//	<---------DEBUG
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

int	ft_red(char *line, char **mtx, int *k, int *i)//	27 lines
{
	char	*tmp;
	int		flg;// serve a contare quanti > (max 2, a 3 da syntax error) o < (max 3) vengono trovati
	int		j;

	j = 0;
	flg = 0;
	if (line[*i] == '<')
		flg = 3;
	else if (line[*i] == '>')
		flg = 2;
	while ((line[*i + j] == '<' || line[*i + j] == '>'))
	{
		if (flg == 0 && line[*i + j] == line[*i + j + 1])
			return (-1);
		flg--;
		j++;
	}
	tmp = malloc(j + 1);
	if (tmp == NULL)
		return (-1);
	ft_strlcpy(tmp, line + *i, j + 1);
	mtx[*k] = tmp;
	*k += 1;
	*i += j;
	printf("line at the end of ft_red : |%s|\n", mtx[*k - 1]);//	<---------DEBUG
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

int	ft_else(char *line, char **mtx, int *k, int *i)
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
	printf("line at the end of ft_else : |%s|\n", mtx[*k - 1]);//	<---------DEBUG
	if (line[*i] == 0)
		return (0);
	return (1);
}
