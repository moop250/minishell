/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:24:59 by pberset           #+#    #+#             */
/*   Updated: 2024/07/15 16:13:53 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_infile(t_pipe_fd *pipeline_in)
{
	if (!pipeline_in || !pipeline_in->file_name)
		return ;
	if (pipeline_in->heredoc)
		handle_heredoc(pipeline_in);
	pipeline_in->fd = open(pipeline_in->file_name, O_RDONLY);
	if (pipeline_in->fd == -1)
	{
		perror(pipeline_in->file_name);
		return ;
	}
	if (dup2(pipeline_in->fd, STDIN_FILENO) == -1)
		perror("dup2");
	if (close(pipeline_in->fd) == -1)
		perror(pipeline_in->file_name);
	if (!ft_strcmp(pipeline_in->file_name, ".heredoc"))
		if (unlink(".heredoc") == -1)
			perror(".heredoc");
}
