/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/15 16:47:17 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_core	*minishell_loop(int ac, char **av, char **env)
{
	t_core	*core;
	t_token	*tmp;

	while (true)
	{
		core = init(ac, av, env);
		core->line = readline(core->prompt->prompt);
		if (!core->line)
			ms_error("readline error");
		//temp exit
		if(ft_strcmp(core->line, "exit") == 0)
		{
			free (core->line);
			break ;
		}
		if (!tokenizer(core->line, core))
			continue ;
		tmp = (*core->token);
		while (tmp)
		{
			ft_printf_fd(core->ms_stdout, "--->%s", tmp->content);
			tmp = tmp->next;
		}
		printf("\n");
		ms_tokensclear(core->token);
		free(core->line);
	}
	return (core);
}
