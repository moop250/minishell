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

void	parent_signals(void)
{
	signal(SIGINT, handle_parent_sig);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	signal(SIGINT, handle_child_sig);
	signal(SIGQUIT, handle_child_sig);
}

void	heredoc_signals(void)
{
	t_core	*core;

	core = get_core();
	core->interact = 1;
	signal(SIGINT, handle_heredoc_sig);
	signal(SIGQUIT, SIG_IGN);
}
