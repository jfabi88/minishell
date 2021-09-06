#include "minishell.h"

void	ft_free_parse_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		ft_free_parse(list->content);
		list = list->next;
		free(tmp);
	}
}

void	ft_free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		free(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

char	*ft_strdel(char *str, int num)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (len - num <= 0)
		return (NULL);
	else
		ret = malloc(len - num + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < len - num)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

static int	ft_list_to_mtx_utils(char *mtx, t_data *d)
{
	int	s_l;

	s_l = ft_strlen(d->env);
	mtx = malloc(ft_strlen(d->content) + s_l + 2);
	if (mtx == NULL)
		return (-1);
	ft_memcpy(mtx, d->env, s_l);
	ft_memcpy(mtx + s_l, "=", 1);
	ft_strlcpy(mtx + s_l + 1, d->content, ft_strlen(d->content) + 1);
	return (0);
}

char	**ft_lst_to_mtx(t_list *list)
{
	int		len;
	char	**mtx;
	t_data	*data;

	mtx = malloc(sizeof(char *) * (ft_data_lst_size(list, 0) + 1));
	if (mtx == NULL)
		return (NULL);
	len = 0;
	while (list)
	{
		data = ((t_data *)(list->content));
		if (data->id == 0)
		{
			if (ft_list_to_mtx_utils(mtx[len], data) == -1)
				return (ft_free_matrix(mtx));
			len++;
		}
		list = list->next;
	}
	mtx[len] = NULL;
	return (mtx);
}
