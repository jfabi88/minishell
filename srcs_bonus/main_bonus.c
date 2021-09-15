/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarzano <lmarzano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:00:27 by lmarzano          #+#    #+#             */
/*   Updated: 2021/09/15 18:00:40 by lmarzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_create_list_env(char *env[], t_list	**var)
{
	int		i;
	char	**matrix;
	t_list	*list;

	i = 0;
	while (env[i])
	{
		matrix = ft_split(env[i], '=');
		if (matrix == NULL)
			return (-1);
		list = ft_new_datalist(matrix[0], matrix[1], 0);
		if (list == 0)
		{
			ft_free_listenv(list);
			return (-1);
		}
		ft_lstadd_back(var, list);
		ft_free_matrix(matrix);
		i++;
	}
	ft_setprev(var);
	return (1);
}

int	ft_execute(t_parse *parse, t_list *list, t_list *var)
{
	int	num;

	if (parse == NULL)
		return (1);
	if (ft_strncmp(parse->command, "echo", 5) == 0)
		num = ft_check_echo(parse);
	else if (ft_strncmp(parse->command, "pwd", 4) == 0)
		num = ft_check_pwd(parse, var);
	else if (ft_strncmp(parse->command, "cd", 3) == 0)
		num = ft_check_cd(parse, var);
	else if (ft_strncmp(parse->command, "exit", 5) == 0)
		num = ft_check_exit(parse, list, var);
	else if (ft_strncmp(parse->command, "export", 7) == 0)
		num = ft_check_export(parse, var);
	else if (ft_strncmp(parse->command, "env", 4) == 0)
		num = ft_check_env(parse, var);
	else if (ft_strncmp(parse->command, "unset", 4) == 0)
		num = ft_check_unset(parse, var);
	else
		num = ft_execute_command(parse, var);
	return (num);
}

int	ft_token_run(t_token *token, t_list *history, t_list *var)
{
	t_parse	*parse;
	char	*tmp;
	int		num;
	int		fd[2];
	int		fd_exec[2];

	num = 0;
	token->line = ft_expand(token->line, var);
	parse = ft_parsing(token->line);
	ft_save_fd(&fd[0], &fd[1]);
	if (ft_open_red(parse->output, &fd_exec[0], &fd_exec[1]) == -1)
		return (ft_add_env(var, "?", "1", 1));
	dup2(fd_exec[0], STDIN_FILENO);
	dup2(fd_exec[1], STDOUT_FILENO);
	num = ft_execute(parse, history, var);
	close(fd_exec[0]);
	close(fd_exec[1]);
	tmp = ft_itoa(num);
	if (tmp != NULL)
		ft_add_env(var, "?", tmp, 1);
	free(tmp);
	ft_restore_fd(fd);
	ft_free_parse(parse);
	return (num);
}

int	main(int argc, char *argv[], char *env[])
{
	char			*line;
	t_list			*var;
	t_list			*list;
	struct termios	origin;
	int				fd[2];

	list = NULL;
	var = NULL;
	tcgetattr(STDIN_FILENO, &origin);
	if (argc < 0 || argv == NULL)
		ft_error(15, 0, NULL);
	if (ft_create_list_env(env, &var) == -1)
		ft_error(16, 0, NULL);
	if (ft_file_history(&list, var) == -1)
		ft_error(17, 0, NULL);
	while (1)
	{
		line = ft_prompt("#mini_hell bonus: ", &list, &origin);
		g_token = ft_tokanizer(line);
		free(line);
		ft_save_fd(&fd[0], &fd[1]);
		ft_running(g_token, list, var, 0);
		ft_restore_fd(fd);
		ft_free_token(g_token);
	}
}
