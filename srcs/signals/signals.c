/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:56 by pberset           #+#    #+#             */
/*   Updated: 2024/08/20 20:36:25 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void	set_signal_handler(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigaddset(&sa.sa_mask, sig);
	sigaction(sig, &sa, NULL);
}

void	parent_signals(void)
{
	set_signal_handler(SIGINT, handle_parent_sig, 0);
	set_signal_handler(SIGQUIT, SIG_IGN, 0);
}

void	child_signals(void)
{
	set_signal_handler(SIGINT, SIG_DFL, 0);
	set_signal_handler(SIGQUIT, handle_child_sig, 0);
}

void	heredoc_signals(void)
{
	t_core	*core;

	core = get_core();
	core->interact = 1;
	set_signal_handler(SIGINT, handle_heredoc_sig, 0);
	set_signal_handler(SIGQUIT, SIG_IGN, 0);
}
