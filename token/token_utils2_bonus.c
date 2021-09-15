/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarzano <lmarzano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:01:05 by lmarzano          #+#    #+#             */
/*   Updated: 2021/09/15 18:01:16 by lmarzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_c(char *line, char c)
{
	int	i;

	i = 0;
	while (line && line[i] == c)
		i++;
	return (i);
}

void	ft_free_token(t_token *token)
{
	if (token)
	{
		free(token->line);
		ft_free_list(token->s_flag);
		ft_free_list(token->flag);
		while (token->s_commands)
		{
			ft_free_token(token->s_commands->content);
			free(token->s_commands);
			token->s_commands = token->s_commands->next;
		}
		while (token->commands)
		{
			ft_free_token(token->commands->content);
			free(token->commands);
			token->commands = token->commands->next;
		}
		free(token);
	}
}

t_token	*ft_init_token(void)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (ret == NULL)
		return (NULL);
	ret->flag = NULL;
	ret->commands = NULL;
	ret->line = NULL;
	ret->s_commands = NULL;
	ret->s_flag = NULL;
	return (ret);
}
