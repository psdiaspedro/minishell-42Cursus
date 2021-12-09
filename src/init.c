/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:57:59 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/06 11:14:11 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	len_env(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

void	get_env(t_mini *mini, char **env)
{
	char	**aux;
	int	len;
	int	i;

	len = len_env(env);
	mini->env->key = malloc(sizeof(char *) * len + 1);
	mini->env->content = malloc(sizeof(char *) * len + 1);
	i = 0;
	while (env[i])
	{
		aux = ft_split(env[i], '=');
		mini->env->key[i] = aux[0];
		mini->env->content[i] = aux[1];
		i++;
	}
}

void	get_path(t_mini *mini)
{
	char	*path;
	char	*aux;
	int		i;

	path = getenv("PATH");
	aux = ft_strdup(path);
	if(!aux)
		return ;
	mini->env->path = ft_split(aux, ':');
	i = 0;
	while (mini->env->path[i])
	{
		mini->env->path[i] = ft_strjoin(mini->env->path[i], "/");
		i++;
	}
	free(aux);
}

void	init(t_mini *mini, char **env)
{
	get_env(mini, env);
	get_path(mini);
	mini->is_open = 0;
}
