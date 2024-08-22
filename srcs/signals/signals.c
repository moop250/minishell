/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:56 by pberset           #+#    #+#             */
/*   Updated: 2024/08/21 19:23:46 by pberset          ###   ########.fr       */
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
	set_signal_handler(SIGINT, handle_child_sig, 0);
	set_signal_handler(SIGQUIT, handle_child_sig, 0);
}

void	heredoc_signals(struct sigaction *sa)
{
	sa->sa_handler = heredoc_handler;
	sigaddset(&sa->sa_mask, SIGINT);
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaddset(&sa->sa_mask, SIGQUIT);
	sigaction(SIGQUIT, sa, NULL);
}
