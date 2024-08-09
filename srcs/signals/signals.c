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

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (!foreground_pid)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			kill(foreground_pid, SIGINT);
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (Core dumped)\n", 19);
		kill(0, sig);
	}
}

void	setup_signals(int sig, void (*handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(sig, &sa, NULL);
}
