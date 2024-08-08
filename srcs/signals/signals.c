/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:56 by pberset           #+#    #+#             */
/*   Updated: 2024/08/08 13:28:13 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			kill(foreground_pid, SIGINT);
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		if (foreground_pid)
		{
			write(STDOUT_FILENO, "Quit (Core dumped)\n", 19);
			kill(foreground_pid, SIGQUIT);
		}
		else
			signal(sig, SIG_IGN);
	}
}

void	setup_signals(void)
{
    struct sigaction	sa_int;
	struct sigaction	sa_quit;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
