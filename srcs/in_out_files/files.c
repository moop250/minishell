/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:18:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/02 14:05:54 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_files(t_pipeline *pipeline)
{
	int	f_error;
	if (pipeline->pipeline_in)
		pipeline->pipeline_in->fd = get_infile_fd(pipeline->pipeline_in);
	if (pipeline->pipeline_in->fd < 0)
	{
		ms_error("infile error\n");
		return ;
	}
	f_error = dup2(pipeline->pipeline_in->fd, STDIN_FILENO);
	if (f_error == -1)
	{
		ms_error("dup2 error\n");
		return ;
	}
}
