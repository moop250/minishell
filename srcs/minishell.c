/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:45:35 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/22 16:15:47 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_core	*core;
	char	**paths;

	core = minishell_loop(ac, av, env);
	close(core->ms_stdin);
	close(core->ms_stdout);
	if (core->token)
		ms_tokensclear(&core->token);
	clear_envs(core->env->rawenvs);
	paths = core->env->paths;
	while (*paths)
	{
		gfree(*paths);
		paths++;
	}
	gfree(core->env->paths);
	gfree(core->env);
	gfree(core);
	return (0);
}