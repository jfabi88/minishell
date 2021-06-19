#include "minishell.h"

void	ft_check_cd(char **stringa)
{
	char	**output;

	output = ft_create_stroutput(stringa);
	ft_free_matrix(output);
}