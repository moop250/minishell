/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:18:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 14:45:52 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_files(t_pipeline *pipeline)
{
	char	*buffer[BUFSIZ];
	ssize_t	bytes_read;
	ssize_t	bytes_written;

	if (pipeline->pipeline_in)
		handle_infile(pipeline->pipeline_in);
	if (pipeline->pipeline_out)
		handle_outfile(pipeline->pipeline_out);
	if (pipeline->pipeline_in && pipeline->pipeline_out)
	{
		while ((bytes_read = read(pipeline->pipeline_in->fd, buffer, sizeof(buffer))) > 0)
    	{
    	    bytes_written = write(pipeline->pipeline_out->fd, buffer, bytes_read);
    	    if (bytes_written != bytes_read)
    	    {
    	        perror("write");
    	        break;
    	    }
    	}
    	if (bytes_read == -1)
    	    perror("read");
	}
	if (close(pipeline->pipeline_in->fd) == -1)
		perror("close infile");
	if (close(pipeline->pipeline_out->fd) < 0)
	{
		perror("close out fd");
		return ;
	}
}
