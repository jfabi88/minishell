#include "minishell.h"

static int ft_error_5(int id, char c)
{
    if (id == 1)
    {
        ft_putstr_fd("#: syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
    }
    else if (id == 2)
    {
        ft_putstr_fd("#: ", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd(": Is a directory\n", 2);
    }
    else if (id == 3)
        ft_putstr_fd("#: syntax error near unexpected token `newline'\n", 2);
    return (-1);
}

int ft_error(int id, char c)
{
    int num;

    if (id < 5)
        num = ft_error_5(id, c);
    return (num);     
}