/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:37:48 by pberset           #+#    #+#             */
/*   Updated: 2024/07/11 16:30:34 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_exec_path(char *cmd, char **path)
{
	int		i;
	char	*exec_path;

	i = 0;
	if (!cmd || !path)
		return (NULL);
	while (path[i])
	{
		exec_path = ft_strjoin(path[i], "/");
		if (!exec_path)
			return (NULL);
		exec_path = ft_strjoin(exec_path, cmd);
		if (!exec_path)
			return (NULL);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		gfree(exec_path);
		i++;
	}
	return (NULL);
}
char	*init_execp(t_pipeline *current, char **paths)
{
	if (!current->params)
		return (NULL);
	if (access(current->params[0], X_OK) == 0)
		return (current->params[0]);
	return (find_exec_path(current->params[0], paths));
}
