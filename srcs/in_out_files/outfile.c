/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:06:41 by pberset           #+#    #+#             */
/*   Updated: 2024/07/15 16:14:11 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_outfile(t_pipe_fd *p_out)
{
	if (p_out->append)
		p_out->fd = open(p_out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		p_out->fd = open(p_out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_out->fd == -1)
	{
		perror(p_out->file_name);
		return ;
	}
	if (dup2(p_out->fd, STDOUT_FILENO) == -1)
		perror("dup2");
}
