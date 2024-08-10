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
#include <readline/readline.h>

void	handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		if (isatty(STDIN_FILENO) && get_core()->interactive)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			get_core()->exit_status = 130;
		}
	}
	else if (signal == SIGQUIT)
	{
		if (isatty(STDIN_FILENO) && get_core()->interactive)
		{
			rl_redisplay();
		}
	}
}

void	toggle_interactive(int mode)
{
	get_core()->interactive = mode;
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
