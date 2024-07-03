/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:06:41 by pberset           #+#    #+#             */
/*   Updated: 2024/07/03 16:28:59 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_outfile(t_pipe_fd *pipeline_out)
{
	int	f_error;

	if (pipeline_out->append)
		pipeline_out->fd = open(pipeline_out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipeline_out->fd = open(pipeline_out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline_out->fd == -1)
		ms_error("outfile error: open error");
	f_error = dup2(pipeline_out->fd, STDOUT_FILENO);
	if (f_error == -1)
		ms_error("dup2 error\n");
}
