/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:11:09 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/08 15:48:46 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_child(t_mini *mini, t_node *node)
{
	int	i;

	i = 3;
	while (i < 150)
	{
		close(i);
		i++;
	}
	get_cmd(mini, node);
	if (find_path(mini, node->str[0]))
	{
		execve(mini->correct_path, node->str, __environ);
		perror("error");
		exit(EXIT_FAILURE);
	}
	if (mini->command_fail == 0)
		exit(g_return);
	else
		exit(0);
}

void	execute(t_mini *mini, t_list *list, t_node *node)
{
	int	pid;

	fd_handler(mini);
	if (is_builtin(node))
		execute_builtin(is_builtin(node), node, mini, list);
	else
	{
		pid = fork();
		signals(2);
		if (pid < 0)
		{
			printf("error\n");
			g_return = 127;
		}
		else if (pid == 0)
			execute_child(mini, node);
		else
			waitpid(pid, &g_return, WUNTRACED);
		if (WIFEXITED(g_return))
			g_return = WEXITSTATUS(g_return);
		else
			g_return = 0;
	}
	dup2(mini->st_out, STDOUT_FILENO);
	dup2(mini->st_in, STDIN_FILENO);
}

int	is_str_quote(char *str, int open)
{
	if (open == 0 && str[0] == D_QUOTE && str[1] == '\0')
		return (1);
	else if (open == 1 && str[0] == D_QUOTE && str[1] == '\0')
		return (0);
	else if (open == 0 && str[0] == S_QUOTE && str[1] == '\0')
		return (1);
	else if (open == 1 && str[0] == S_QUOTE && str[1] == '\0')
		return (0);
	return (0);
}

void	run_cmd(t_mini *mini, t_list *list, t_node *node)
{
	int	i;
	int	result;
	int	open;

	i = 0;
	result = 1;
	open = 0;
	if (node != NULL)
	{
		while (node->str[i] && result)
		{
			if (is_this_quote(node->str[i]))
				open = is_str_quote(node->str[i], open);
			//result = get_result(mini, node, open, i);
			i++;
		}
		if (!result)
			printf("error\n");
		else if (result)
		{
			if (mini->in != -1)
				execute(mini, list, node);
		}
	}
}

void	run(t_mini *mini, t_list *list, int i)
{
	t_node	*node;
	int		fd[2];

	node = list->begin;
	mini->st_out = dup(STDOUT_FILENO);
	mini->st_in = dup(STDIN_FILENO);
	while (i < mini->pipe)
	{
		if (pipe(fd) < 0)
			printf("error\n");
		mini->out = fd[1];
		run_cmd(mini, list, node);
		close(fd[1]);
		if (mini->in != 0)
			close(mini->in);
		mini->in = fd[0];
		node = node->next;
		i++;
	}
	if (list->size > 0)
	{
		run_cmd(mini, list, node);
		close(mini->st_out);
		close(mini->st_in);
	}
}
