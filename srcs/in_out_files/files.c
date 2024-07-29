/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:18:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/27 18:38:49 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_files(t_pipeline *pipeline)
{
	if (pipeline->pipeline_in)
	{
		if (handle_infile(pipeline->pipeline_in) < 0)
			return (-1);
	}
	if (pipeline->pipeline_out)
	{
		if (handle_outfile(pipeline->pipeline_out) < 0)
			return (-1);
	}
	return (0);
}
