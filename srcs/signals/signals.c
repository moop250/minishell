/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:56 by pberset           #+#    #+#             */
/*   Updated: 2024/08/08 14:57:05 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		if (!foreground_pid)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			write(STDOUT_FILENO, "\n", 1);
			kill(foreground_pid, SIGINT);
		}
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (Core dumped)\n", 19);
		kill(foreground_pid, SIGQUIT);
	}
}

void	setup_signals(int sig, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(sig, &sa, NULL);
}
