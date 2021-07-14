#include "minishell.h"

char	*ft_m_strlcpy(char *str, int len)
{
	char	*ret;

	if (len == 0)
		return (NULL);
	ret = malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, str, len + 1);
	return (ret);
}