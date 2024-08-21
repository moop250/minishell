/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:15:56 by pberset           #+#    #+#             */
/*   Updated: 2024/08/20 20:41:49 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_parent_sig(int sig)
{
	t_core	*core;

	core = get_core();
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, core->line, ft_strlen(core->line));
	}
}

void	handle_child_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		set_signal_handler(sig, SIG_DFL, 0);
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dump)\n", 17);
	}
}

void	handle_heredoc_sig(int sig)
{
	t_core	*core;

	core = get_core();
	if (sig == SIGINT)
	{
		core->interact = 0;
		close(STDIN_FILENO);
	}
}
