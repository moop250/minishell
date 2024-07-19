/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:06:41 by pberset           #+#    #+#             */
/*   Updated: 2024/07/19 21:59:16 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_outfile(t_pipe_fd *p_out)
{
	if (p_out->append)
		p_out->fd = open(p_out->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		p_out->fd = open(p_out->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p_out->fd == -1)
	{
		perror(p_out->file_name);
		return (1);
	}
	if (p_out->next)
	{
		close(p_out->fd);
		return (handle_outfile(p_out->next));
	}
	if (dup2(p_out->fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(p_out->fd);
	return (0);
}
