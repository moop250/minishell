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

void	setup_signals(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}

void	child_signals(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = sigquit_handler;
	sigaction(SIGQUIT, sa, NULL);
}
