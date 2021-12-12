/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/12 16:41:35 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	main(void)
{
	t_mini		mini;
	t_list		*list;

	mini.env = create_list_env();
	init(&mini, __environ);
	while (1)
	{
		list = create_list();
		get_input(&mini);
		if(ft_strlen(mini.input) != 0)
		{
			if(split_cmd(&mini, list))
			{
				execute(&mini, list);
				//print_elements(list);
			}
			free_em_all(&mini, list);
		}
		else
			free(list);
	}
	free_minishell(&mini);
	return (0);
}
