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

int	ft_data_lst_size(t_list *data_list, int id)
{
	t_data	*data;
	int		ret;

	ret = 0;
	while (data_list)
	{
		data = data_list->content;
		if (data->id == id || id == 2)
			ret++;
		data_list = data_list->next;
	}
	return (ret);
}

char	**ft_lst_to_mtx(t_list *list)
{
	int		len;
	int		s_l;
	char	**mtx;
	t_data	*d;

	len = ft_data_lst_size(list, 0);
	mtx = malloc(sizeof(char *) * (len + 1));
	if (mtx == NULL)
		return (NULL);
	len = 0;
	while (list)
	{
		d = ((t_data *)(list->content));
		if (d->id == 0)
		{
			s_l = ft_strlen(d->env);
			mtx[len] = malloc(ft_strlen(d->content) + s_l + 2);
			if (mtx[len] == NULL)
				return (ft_free_matrix(mtx));
			ft_memcpy(mtx[len], d->env, s_l);
			ft_memcpy(mtx[len] + s_l, "=", 1);
			ft_strlcpy(mtx[len] + s_l + 1, d->content, ft_strlen(d->content) + 1);
			len++;
		}
		list = list->next;
	}
	mtx[len] = NULL;
	return (mtx);
}

void	*ft_free_null(void	*obj)
{
	free(obj);
	return (NULL);
}

int	ft_find_strposition(char *str, char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], str, ft_strlen(str) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free_data(t_data *data)
{
	t_data	*d;

	d = data;
	free(d->content);
	free(d->env);
	free (data);
}
