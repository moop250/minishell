/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:47:31 by pberset           #+#    #+#             */
/*   Updated: 2024/07/29 22:02:13 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*swap_names(char *old, char *new)
{
	gfree(old);
	return (ft_strdup(new));
}

static void	w_heredoc(char *eof)
{
	ft_printf_fd(1, "warning: heredoc closed by EOF instead of \"%s\"\n", eof);
}

int	handle_heredoc(t_pipe_fd *p_in)
{
	char	*input;

	p_in->fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_in->fd == -1)
	{
		perror(".heredoc open");
		return (1);
	}
	while (42)
	{
		input = readline("heredoc> ");
		if (!input || (ft_strlen(p_in->file_name) == ft_strlen(input) \
			&& !ft_strncmp(input, p_in->file_name, ft_strlen(p_in->file_name))))
			break ;
		ft_putstr_fd(input, p_in->fd);
		ft_putchar_fd('\n', p_in->fd);
		gfree(input);
	}
	if (!input)
		w_heredoc(p_in->file_name);
	gfree(input);
	close(p_in->fd);
	p_in->file_name = swap_names(p_in->file_name, ".heredoc");
	p_in->heredoc = false;
	return (0);
}
