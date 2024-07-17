/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:45:35 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/17 17:22:02 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"

void	ms_freeall(t_core *core)
{
	close(core->ms_stdin);
	close(core->ms_stdout);
	if (core->token)
		ms_tokensclear(&core->token);
	if (core->pipeline)
		ms_pipelinesclear(&core->pipeline);
	clear_envs(core->env->rawenvs);
	ft_2dfree(core->env->paths);
	if (core->env->hasenv)
		free(core->env->hostname);
	gfree(core->env);
	gfree(core);
}

int	main(int ac, char **av, char **env)
{
	t_core	*core;

	core = minishell_loop(ac, av, env);
	ms_freeall(core);
	return (0);
}
