/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:18:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 15:15:53 by pberset          ###   ########.fr       */
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
	if (close(p_in->fd) == -1)
		perror("close infile");
	if (close(p_out->fd) < 0)
	{
		perror("close out fd");
		return ;
	}
}

void	handle_files(t_pipeline *pipeline)
{
	if (pipeline->pipeline_in)
		handle_infile(pipeline->pipeline_in);
	if (pipeline->pipeline_out)
		handle_outfile(pipeline->pipeline_out);
	if (pipeline->pipeline_in != NULL && pipeline->pipeline_out != NULL)
		in_and_out(pipeline->pipeline_in, pipeline->pipeline_out);
}
