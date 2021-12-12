/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:35:22 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/12 16:39:52 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	miniexit(t_mini *mini, t_list *list)
{
	free_em_all(mini, list);
	free_minishell(mini);
	exit(0);
}
