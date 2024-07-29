/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:45:35 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/29 12:39:38 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"

void	ms_freeall(t_core *core)
{
	ms_tokensclear(&core->token);
	ms_pipelinesclear(&core->pipeline);
	clear_envs(core->env->rawenvs);
	ft_2dfree((void **)core->env->paths);
	if (core->env->hasenv)
		gfree(core->env->hostname);
	gfree(core->env->cwd);
	ft_2dfree((void **)core->env->envp);
	gfree(core->env);
	gfree(core);
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
}

static void	ignore_ctrl(void)
{
	struct termios	new_term;

	tcgetattr(1, &new_term);
	new_term.c_lflag |= ECHO;
	new_term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(1, TCSANOW, &new_term);
}

int	main(int ac, char **av, char **env)
{
	t_core	*core;

	ignore_ctrl();
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		printf("Failed to register SIGINT\n");
		return (1);
	}
	core = minishell_loop(ac, av, env);
	ms_freeall(core);
	razegarbage();
	return (0);
}
