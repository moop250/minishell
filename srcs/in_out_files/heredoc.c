/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:47:31 by pberset           #+#    #+#             */
/*   Updated: 2024/07/04 10:39:03 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_pipe_fd *pipeline_in)
{
	char	*input;

	input = "";
	pipeline_in->fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline_in->fd == -1)
		ms_error("infile error: open error");
	while (42)
	{
		input = readline("> ");
		if (ft_strlen(pipeline_in->file_name) == ft_strlen(input) \
			&& !ft_strncmp(input, pipeline_in->file_name, ft_strlen(pipeline_in->file_name)))
			break ;
		ft_putstr_fd(input, pipeline_in->fd);
		ft_putchar_fd('\n', pipeline_in->fd);
		free(input);
	}
	free(input);
	close(pipeline_in->fd);
	free(pipeline_in->file_name);
	pipeline_in->file_name = ft_strdup(".heredoc");
	pipeline_in->heredoc = false;
	handle_infile(pipeline_in);
}