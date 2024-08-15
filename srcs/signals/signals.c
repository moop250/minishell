/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:56 by pberset           #+#    #+#             */
/*   Updated: 2024/08/10 19:55:32 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sig(int signal)
{
	if (isatty(STDIN_FILENO))
	{
		if (signal == SIGINT)
		{
			if (interactive)
			{
				write(1, "\n", 1);
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
			else
				write(1, "\n", 1);
		}
		else if (signal == SIGQUIT)
		{
			if (interactive)
			{
				rl_redisplay();
			}
			else
				write(1, "Quit (core dump)\n", 17);
		}
	}
}

void	toggle_interactive(int mode)
{
	interactive = mode;
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
		interactive = -1;
}

void	heredoc_signals(void)
{
	toggle_interactive(1);
	signal(SIGINT, handle_heredoc_signal);
}
