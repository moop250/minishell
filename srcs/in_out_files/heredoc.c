/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:47:31 by pberset           #+#    #+#             */
/*   Updated: 2024/07/19 17:23:17 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc(t_pipe_fd *p_in)
{
	char	*input;

	input = "";
	p_in->fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_in->fd == -1)
	{
		perror(".heredoc open");
		return (1);
	}
	while (42)
	{
		input = readline("heredoc> ");
		if (ft_strlen(p_in->file_name) == ft_strlen(input) \
			&& !ft_strncmp(input, p_in->file_name, ft_strlen(p_in->file_name)))
			break ;
		ft_putstr_fd(input, p_in->fd);
		ft_putchar_fd('\n', p_in->fd);
		free(input);
	}
	free(input);
	if (close(p_in->fd) == -1)
		perror(".heredoc close");
	free(p_in->file_name);
	p_in->file_name = ft_strdup(".heredoc");
	p_in->heredoc = false;
	return (0);
}
