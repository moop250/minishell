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
#include <unistd.h>

void	handle_sig(int sig)
{
	if (isatty(STDIN_FILENO))
	{
		if (sig == SIGINT)
		{
			if (g_interactive)
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
			if (g_interactive)
				rl_redisplay();
			else
			{
				write(STDERR_FILENO, "Quit (core dump)\n", 17);
				signal(sig, SIG_DFL);
			}
		}
	}
}

void	toggle_interactive(int mode)
{
	g_interactive = mode;
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
	if (sig == SIGINT)
	{
		g_interactive = 0;
		signal(SIGINT, SIG_DFL);
		close(STDIN_FILENO);
	}
}

void	heredoc_signals(void)
{
	g_interactive = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_heredoc_signal);
}
