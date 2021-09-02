#include "minishell.h"

char	*ft_m_strlcpy(char *str, int len)
{
	char	*ret;

	if (len == 0)
		return (NULL);
	ret = malloc(len);
	if (ret == NULL)
		return (NULL);
	if (str == NULL)
		ret[0] = 0;
	else
		ft_strlcpy(ret, str, len);
	return (ret);
}
