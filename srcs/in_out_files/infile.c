/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:24:59 by pberset           #+#    #+#             */
/*   Updated: 2024/07/27 18:39:34 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_infile(t_pipe_fd *pipeline_in)
{
	if (!pipeline_in || !pipeline_in->file_name)
		return (-2);
	if (pipeline_in->heredoc)
		if (handle_heredoc(pipeline_in) != 0)
			return (-1);
	pipeline_in->fd = open(pipeline_in->file_name, O_RDONLY);
	if (pipeline_in->fd == -1)
	{
		perror(pipeline_in->file_name);
		return (-1);
	}
	if (pipeline_in->next)
	{
		close(pipeline_in->fd);
		return (handle_infile(pipeline_in->next));
	}
	if (dup2(pipeline_in->fd, STDIN_FILENO) == -1)
		perror("dup2");
	close(pipeline_in->fd);
	if (!ft_strcmp(pipeline_in->file_name, ".heredoc"))
		if (unlink(".heredoc") == -1)
			perror("unlink");
	return (0);
}
