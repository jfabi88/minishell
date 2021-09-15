/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarzano <lmarzano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:00:36 by lmarzano          #+#    #+#             */
/*   Updated: 2021/09/15 18:00:40 by lmarzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_run_commands(t_token *token, int num, t_list *var, t_list *list)
{
	t_list	*commands;
	t_list	*flag;

	commands = token->commands;
	flag = token->flag;
	while (commands)
	{
		if (num == 0 && ft_strncmp(flag->content, "&&", 3) == 0)
			num = ft_running(commands->content, list, var, 0);
		else if ((num > 0) && ft_strncmp(flag->content, "||", 3) == 0)
			num = ft_running(commands->content, list, var, 0);
		commands = commands->next;
		flag = flag->next;
	}
	return (num);
}

static int	ft_run_s_commands(t_token *token, int num, t_list *var, t_list *lst)
{
	t_list	*commands;
	t_list	*flag;

	commands = token->s_commands;
	flag = token->s_flag;
	while (commands)
	{
		if (num == 0 && ft_strncmp(flag->content, "&&", 3) == 0)
			num = ft_running(commands->content, lst, var, 0);
		else if ((num > 0) && ft_strncmp(flag->content, "||", 3) == 0)
			num = ft_running(commands->content, lst, var, 0);
		commands = commands->next;
		flag = flag->next;
	}
	return (num);
}

static int	ft_token_pipe(t_token *token, t_list *history, t_list *var, int num)
{
	int	fork_id;
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	fork_id = fork();
	if (fork_id < 0)
		return (-1);
	else if (fork_id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit (ft_running(token, history, var, num));
	}
	else
	{
		waitpid(fork_id, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		return (1);
	}
}

int	ft_running(t_token *t, t_list *history, t_list *var, int d)
{
	int		num;

	if (t && d == 0 && t->s_commands && !ft_strncmp(t->s_flag->content, "|", 2))
	{
		num = ft_token_pipe(t, history, var, 1);
		if (num == -1)
			return (-1);
		ft_running(t->s_commands->content, history, var, 0);
		ft_running(t->commands->content, history, var, 0);
	}
	else if (t && d < 2 && t->commands && !ft_strncmp(t->flag->content, "|", 2))
	{
		num = ft_token_pipe(t, history, var, d + 2);
		if (num == -1)
			return (-1);
		ft_running(t->commands->content, history, var, 0);
		ft_running(t->s_commands->content, history, var, 0);
	}
	else if (t)
	{
		num = ft_token_run(t, history, var);
		num = ft_run_s_commands(t, num, var, history);
		num = ft_run_commands(t, num, var, history);
	}
	return (num);
}
