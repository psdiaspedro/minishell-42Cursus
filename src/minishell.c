/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/11/30 20:48:51 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



int	main(void)
{
	t_mini	mini;


	init(&mini);
	while (1)
	{
		get_input(&mini);
		process_input(&mini);
		// execute_cmd(&mini, mini.input_parsed[0]);
		free(mini.input);
	}
	return (0);
}
