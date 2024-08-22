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

void	setup_signals(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaddset(&sa->sa_mask, SIGINT);
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaddset(&sa->sa_mask, SIGQUIT);
	sigaction(SIGQUIT, sa, NULL);
}

void	child_signals(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigaddset(&sa->sa_mask, SIGINT);
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = sigquit_handler;
	sigaddset(&sa->sa_mask, SIGQUIT);
	sigaction(SIGQUIT, sa, NULL);
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
