/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:23 by pberset           #+#    #+#             */
/*   Updated: 2024/07/19 18:32:51 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_one(t_pipeline *pipeline, char **paths, char **env)
{
	pipeline->execp = init_execp(pipeline, paths);
	if (!pipeline->execp)
	{
		ft_printf_fd(2, "%s: command not found\n", pipeline->params[0]);
		exit(127);
	}
	if (execve(pipeline->execp, pipeline->params, env) < 0)
	{
		exec_err(NULL, pipeline->execp, "execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
