/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:18:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/19 18:35:37 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	in_and_out(t_pipe_fd *p_in, t_pipe_fd*p_out)
{
	char	*buffer[BUFSIZ];
	ssize_t	bytes_read;
	ssize_t	bytes_written;

	while ((bytes_read = read(p_in->fd, buffer, sizeof(buffer))) > 0)
	{
		bytes_written = write(p_out->fd, buffer, bytes_read);
		if (bytes_written != bytes_read)
		{
			perror("write");
			break;
		}
	}
	if (bytes_read == -1)
		perror("read");
}

int	handle_files(t_pipeline *pipeline)
{
	int	buf_fd[2];

	buf_fd[0] = -1;
	buf_fd[1] = -1;
	if (pipeline->pipeline_in)
	{
		buf_fd[0] = dup(STDIN_FILENO);
		if (handle_infile(pipeline->pipeline_in) != 0)
			return (1);
	}
	if (pipeline->pipeline_out)
	{
		buf_fd[1] = dup(STDOUT_FILENO);
		if (handle_outfile(pipeline->pipeline_out) != 0)
			return (1);
	}
	if (pipeline->pipeline_in != NULL && pipeline->pipeline_out != NULL)
		in_and_out(pipeline->pipeline_in, pipeline->pipeline_out);
	if (buf_fd[0] != -1)
	{
		dup2(buf_fd[0], STDIN_FILENO);
		close(buf_fd[0]);
	}
	if (buf_fd[1] != -1)
	{
		dup2(buf_fd[1], STDOUT_FILENO);
		close(buf_fd[1]);
	}
	if (pipeline->next == NULL)
	{
		if (pipeline->pipeline_in && pipeline->pipeline_in->fd != -1 \
			&& pipeline->params[0] == NULL)
			close(pipeline->pipeline_in->fd);
		if (pipeline->pipeline_out && pipeline->pipeline_out->fd != -1 \
			&& pipeline->params[0] == NULL)
			close(pipeline->pipeline_out->fd);
	}
	return (0);
}
