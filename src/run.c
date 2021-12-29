/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:11:09 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/29 15:31:52 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fd_handler(t_mini *mini)
{
	if (mini->in != 0)
	{
		dup2(mini->in, 0);
		close(mini->in);
	}
	if (mini->out != 1)
	{
		dup2(mini->out, 1);
		close(mini->out);
	}
}

void	execute_child(t_mini *mini, t_node *node)
{
	get_cmd(mini, node);
	if (find_path(mini, node->str[0]))
	{
		execve(mini->correct_path, node->str, __environ);
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	execute(t_mini *mini, t_list *list, t_node *node)
{
	int	pid;
	int	status;

	mini->st_out = dup(STDOUT_FILENO);
	mini->st_in = dup(STDIN_FILENO);
	fd_handler(mini);
	if (is_builtin(node))
		execute_builtin(is_builtin(node), node, mini, list);
	else
	{
		signals(2);
		pid = fork();
		if (pid < 0)
			printf("error\n");
		else if (pid == 0)
			execute_child(mini, node);
		else
			waitpid(pid, &status, 0);
		if(WIFEXITED(status))
			g_return = WEXITSTATUS(status);
		else
			g_return = 0;
	}
	dup2(mini->st_out, STDOUT_FILENO);
	dup2(mini->st_in, STDIN_FILENO);
}

void	run_cmd(t_mini *mini, t_list *list, t_node *node)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	if (node != NULL)
	{
		while (node->str[i] && result)
		{
			if (!ft_strcmp(node->str[i], ">") || !ft_strcmp(node->str[i], ">>"))
				result = redirect_out(mini, node, i);
			if (!ft_strcmp(node->str[i], "<") || !ft_strcmp(node->str[i], "<<"))
				result = redirect_in(mini, node, i);
			i++;
		}
		if (!result)
			printf("error bla\n");
		else if (result)
			execute(mini, list, node);
	}
}

void	run(t_mini *mini, t_list *list)
{
	t_node	*node;
	int		i;
	int		fd[2];

	node = list->begin;
	i = 0;
	while (i < mini->pipe)
	{
		if (pipe(fd) < 0)
			printf("error\n");
		mini->out = dup(fd[1]);
		run_cmd(mini, list, node);
		close(mini->out);
		if (mini->in != 0)
			close(mini->in);
		mini->in = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		node = node->next;
		i++;
	}
	if (list->size > 0)
		run_cmd(mini, list, node);
	// else
	// 	printf("error\n");
}
