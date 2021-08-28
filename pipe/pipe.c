#include "minishell.h"

void ft_list_pipe(char *line, t_list **list)
{
    int     i;
    int     j;
    char    *tmp;
    t_list  *ret;

    i = 0;
    j = 0;
    ret = NULL;
    while (line[i])
    {
        if (line[i] == '|' && !ft_is_in_quotes(line, i, '\'', '"'))
        {
            tmp = ft_m_strlcpy(line + j, i - j + 1);
            if (tmp ==  NULL)
                return (ft_free_list(ret));
            ft_lst_add_content(tmp, &ret, 2);
            j = i + 1;
        }
        i++;
    }
    tmp = ft_m_strlcpy(line + j, i - j + 1);
    if (tmp == NULL)
        return (ft_free_list(ret));
    ft_lst_add_content(tmp, &ret, 2);
    *list = ret;
}