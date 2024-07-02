/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:18:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/02 14:49:55 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_files(t_pipeline *pipeline)
{
	if (pipeline->pipeline_in)
		handle_infile(pipeline->pipeline_in);
}
