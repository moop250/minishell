/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:45:35 by hlibine           #+#    #+#             */
/*   Updated: 2024/08/08 14:56:38 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
#include <termios.h>
#include <unistd.h>

volatile pid_t	foreground_pid;

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

static void	disable_canonical(struct termios *term)
{
	tcgetattr(STDOUT_FILENO, term);
	term->c_lflag |= FLUSHO;
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
}

static void	restore_term(struct termios *term)
{
	term->c_lflag &= ~FLUSHO;
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
}

int	main(int ac, char **av, char **env)
{
	t_core			*core;
	struct termios	term;

	disable_canonical(&term);
	foreground_pid = 0;
	setup_signals(SIGINT, handle_sigint);
	setup_signals(SIGQUIT, SIG_IGN);
	core = minishell_loop(ac, av, env);
	ms_freeall(core);
	razegarbage();
	restore_term(&term);
	return (0);
}
