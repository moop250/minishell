/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:24:59 by pberset           #+#    #+#             */
/*   Updated: 2024/07/02 13:49:15 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_infile_fd(t_pipe_fd *pipeline_in)
{
	int	fd;

	if (!pipeline_in || !pipeline_in->file_name)
		return (-2);
	fd = open(pipeline_in->file_name, O_RDONLY);
	return (fd);
}
