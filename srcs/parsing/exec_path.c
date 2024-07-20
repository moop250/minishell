/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:37:48 by pberset           #+#    #+#             */
/*   Updated: 2024/07/20 10:59:53 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_exec_path(char *cmd, char **path)
{
	int		i;
	char	*buff;
	char	*exec_path;

	i = 0;
	if (!cmd || !path)
		return (NULL);
	while (path[i])
	{
		buff = ft_strjoin(path[i], "/");
		if (!buff)
			return (NULL);
		exec_path = ft_strjoin(buff, cmd);
		free(buff);
		if (!exec_path)
			return (NULL);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	ft_printf_fd(1, "%s: Unknown command...\n", cmd);
	return (NULL);
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || \
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") || \
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

char	*init_execp(t_pipeline *current, char **paths)
{
	if (!current->params)
		return (NULL);
	if (access(current->params[0], X_OK) == 0)
		return (current->params[0]);
	if (is_builtin(current->params[0]))
		return ("builtin");
	return (find_exec_path(current->params[0], paths));
}
