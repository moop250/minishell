/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:37:48 by pberset           #+#    #+#             */
/*   Updated: 2024/06/21 13:38:12 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (NULL);
			return (ft_split(path, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*find_exec_path(char *cmd, char **path)
{
	int		i;
	char	*exec_path;

	i = 0;
	while (path[i])
	{
		exec_path = ft_strjoin(path[i], "/");
		if (!exec_path)
			return (NULL);
		exec_path = ft_strjoin(exec_path, cmd);
		if (!exec_path)
			return (NULL);
		if (access(exec_path, F_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}
