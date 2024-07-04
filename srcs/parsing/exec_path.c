/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:37:48 by pberset           #+#    #+#             */
/*   Updated: 2024/07/04 15:30:36 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_exec_path(char *cmd, char **path)
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
