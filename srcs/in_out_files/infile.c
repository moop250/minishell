/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:24:59 by pberset           #+#    #+#             */
/*   Updated: 2024/07/02 14:49:51 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_infile(t_pipe_fd *pipeline_in)
{
	int	f_error;

	if (!pipeline_in || !pipeline_in->file_name)
		ms_error("infile error: no file name");
	pipeline_in->fd = open(pipeline_in->file_name, O_RDONLY);
	if (pipeline_in->fd == -1)
		ms_error("infile error: open error");
	f_error = dup2(pipeline_in->fd, STDIN_FILENO);
	close(pipeline_in->fd);
	if (f_error == -1)
		ms_error("dup2 error\n");
}
