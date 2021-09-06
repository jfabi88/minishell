/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfabi <jfabi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:19:14 by jfabi             #+#    #+#             */
/*   Updated: 2021/07/09 11:20:41 by jfabi            ###   ########.fr       */
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

static int	ft_go(t_list *parse_list, t_list *history, t_list *var)
{
	int		num;
	int		fd[2];
	t_parse	*data;

	if (parse_list && parse_list->next)
	{
		data = ((t_parse *)(parse_list->next)->content);
		num = ft_exec_pipe(parse_list->content, data, history, var);
		if (num == -1)
			return (num);
		return (ft_go(parse_list->next, history, var));
	}
	if (parse_list && parse_list->prev != NULL)
		num = ft_execute(parse_list->content, history, var);
	else if (parse_list && parse_list->prev == NULL)
	{
		ft_open_red(((t_parse *)(parse_list->content))->output, &fd[0], &fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		num = ft_execute(parse_list->content, history, var);
	}
	return (num);
}

static int	ft_run(t_token *token, t_list *history, t_list *var)
{
	t_parse	*parse;
	int		num;
	int		fd[2];

	num = 0;
	token->line = ft_expand(token->line, var);
	parse = ft_parsing(token->line);
	//parse_list = ft_list_parse(token->line);
	//ft_save_fd(&fd[0], &fd[1]);
	num = ft_execute(parse, history, var);
	ft_add_env(var, "?", ft_itoa(num), 1);
	//ft_restore_fd(fd);
	ft_free_parse(parse);
	return (num);
}

static int	ft_run_commands(t_token *token, int num, t_list *var, t_list *list)
{
	t_list	*commands;
	t_list	*flag;

	commands = token->commands;
	flag = token->flag;
	while (commands)
	{
		if (num >= 0 && ft_strncmp(flag->content, "&&", 3) == 0)
			num = ft_running(commands->content, list, var, 0);
		else if ((num == -1) && ft_strncmp(flag->content, "||", 3) == 0)
			num = ft_running(commands->content, list, var, 0);
		commands = commands->next;
		flag = flag->next;
	}
	return (num);
}

static int	ft_run_s_commands(t_token *token, int num, t_list *var, t_list *list)
{
	t_list	*commands;
	t_list	*flag;

	commands = token->s_commands;
	flag = token->s_flag;
	while (commands)
	{
		if (num >= 0 && ft_strncmp(flag->content, "&&", 3) == 0)
			num = ft_running(commands->content, list, var, 0);
		else if ((num == -1)  && ft_strncmp(flag->content, "||", 3) == 0)
			num = ft_running(commands->content, list, var, 0);
		commands = commands->next;
		flag = flag->next;
	}
	return (num);
}

int	ft_run_token(t_token *token, t_list *history, t_list *var)
{
	int	num;

	num = ft_run(token, history, var);
	num = ft_run_s_commands(token, num, var, history);
	num = ft_run_commands(token, num, var, history);
	return (num);
}

int	ft_token_pipe(t_token *token, t_list *history, t_list *var, int num)
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

int	ft_running(t_token *token, t_list *history, t_list *var, int id)
{
	int		num;

	if (id == 0 && token->s_commands && !ft_strncmp(token->s_flag->content, "|", 2))
	{
		num = ft_token_pipe(token, history, var, 1);
		if (num == -1)
			return (-1);
		ft_running(token->s_commands->content, history, var, 0);
	}
	else if (id < 2 && token->commands && !ft_strncmp(token->flag->content, "|", 2))
	{
		num = ft_token_pipe(token, history, var, id + 2);
		if (num == -1)
			return (-1);
		ft_running(token->commands->content, history, var, 0);
	}
	else
	{
		num = ft_run(token, history, var);
		if (id == 2 || id == 0)
			num = ft_run_s_commands(token, num, var, history);
		if (id == 1 || id == 0)
			num = ft_run_commands(token, num, var, history);
	}
	return (num);
}


int	main(int argc, char *argv[], char *env[])
{
	char			*line;
	t_list			*var;
	t_list			*list;
	struct termios	origin;
	int				fd[2];

	tcgetattr(STDIN_FILENO, &origin);
	list = NULL;
	if (argc < 0 || argv == NULL)
		ft_error(15, 0, NULL);
	var = NULL;
	if (ft_create_list_env(env, &var) == -1)
		ft_error(16, 0, NULL);
	if (ft_file_history(&list, var) == -1)
		ft_error(17, 0, NULL);
	line = ft_prompt("# Orders, my Lord? ", &list, &origin);
	while (1)
	{
		g_token = ft_tokanizer(line);
		free(line);
		//ft_print_token(g_token);
		ft_save_fd(&fd[0], &fd[1]);
		if (g_token)
			ft_running(g_token, list, var, 0);
		ft_restore_fd(fd);
		ft_free_token(g_token);
		line = ft_prompt("# Orders, my Lord? ", &list, &origin);
	}
}
