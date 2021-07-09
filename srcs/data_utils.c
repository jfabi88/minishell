#include "minishell.h"

t_data	*ft_malloc_data(int size_env, int size_content)
{
	t_data	*data;

	data = malloc(sizeof(t_data *));
	if (data == NULL)
		return (NULL);
	data->env = malloc(size_env + 1);
	if (data->env == NULL)
	{
		free(data);
		return (NULL);
	}
	data->content = malloc(size_content + 1);
	if (data->content == NULL)
	{
		free(data->env);
		free(data);
		return (NULL);
	}
	return (data);
}

t_list	*ft_new_datalist(const char *env, const char *content)
{
	t_data	*data;
	t_list	*list;
	int		len_env;
	int		len_content;

	if (content == NULL)
		len_content = 0;
	else
		len_content = ft_strlen(content);
	len_env = ft_strlen(env);
	data = ft_malloc_data(len_env, len_content);
	if (data == NULL)
		return (NULL);
	ft_strlcpy(data->env, env, len_env + 1);
	ft_strlcpy(data->content, content, len_content + 1);
	list = ft_lstnew(data);
	if (list == NULL)
		ft_free_data(data);
	return (list);
}