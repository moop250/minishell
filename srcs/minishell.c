/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:45:35 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/19 21:46:21 by pberset          ###   ########.fr       */
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
	ft_2dfree((void **)core->env->paths);
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
