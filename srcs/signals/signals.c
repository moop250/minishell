/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:56 by pberset           #+#    #+#             */
/*   Updated: 2024/08/20 13:02:32 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sig(int sig)
{
	t_core	*core;

	core = get_core();
	if (sig == SIGINT)
	{
		if (core->interact)
		{
			write(STDERR_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(STDERR_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (core->interact)
			rl_redisplay();
		else
		{
			write(STDERR_FILENO, "Quit (core dump)\n", 17);
			signal(sig, SIG_DFL);
		}
	}
}

void	toggle_interactive(int mode)
{
	t_core	*core;

	core = get_core();
	core->interact = mode;
	if (mode)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, handle_sig);
}

void	setup_signals(void)
{
	toggle_interactive(1);
	signal(SIGINT, handle_sig);
}

void	handle_heredoc_signal(int sig)
{
	t_core	*core;

	core = get_core();
	if (sig == SIGINT)
	{
		core->interact = 0;
		signal(SIGINT, SIG_DFL);
		close(STDIN_FILENO);
	}
}

void	heredoc_signals(void)
{
	t_core	*core;

	core = get_core();
	core->interact = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc_signal);
}