#include "minishell.h"

char	*ft_get_pwd(void)
{
	char	*pwd;

	pwd = malloc(4097);
	getcwd(pwd, 4097);
	return (pwd);
}

static int	ft_pwd(int fd, t_list *var)
{
	char	*pwd;

	pwd = malloc(4097);
	getcwd(pwd, 4097);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, fd);
		ft_putchar_fd('\n', fd);
		return (0);
	}
	return (1);
}

int	ft_check_pwd(t_parse *parse, t_list *var)
{
	int	num;

	num = ft_pwd(1, var);
	return (num);
}
