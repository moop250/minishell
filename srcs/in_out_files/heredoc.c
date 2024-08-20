/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:47:31 by pberset           #+#    #+#             */
/*   Updated: 2024/08/20 13:02:53 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*swap_names(char *old, char *new)
{
	gfree(old);
	g_interactive = 0;
	return (ft_strdup(new));
}

static void	w_heredoc(char *eof)
{
	ft_printf_fd(STDERR_FILENO, "warning: heredoc closed by EOF instead of \"%s\"\n", eof);
}

static void	cleanup(char *input, t_pipe_fd *p_in)
{
	gfree(input);
	close(p_in->fd);
	p_in->heredoc = false;
}

int	handle_heredoc(t_pipe_fd *p_in)
{
	char	*input;

	heredoc_signals();
	p_in->fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (g_interactive > 0)
	{
		if (g_interactive > 0)
			input = readline("heredoc> ");
		if (!input || !g_interactive || (ft_strlen(p_in->file_name) == ft_strlen(input) \
			&& !ft_strncmp(input, p_in->file_name, ft_strlen(p_in->file_name))))
			break ;
		ft_putstr_fd(input, p_in->fd);
		ft_putchar_fd('\n', p_in->fd);
		gfree(input);
	}
	if (!input && g_interactive > 0)
		w_heredoc(p_in->file_name);
	cleanup(input, p_in);
	if (g_interactive > 0)
	{
		p_in->file_name = swap_names(p_in->file_name, ".heredoc");
		return (0);
	}
	return (-1);
}
