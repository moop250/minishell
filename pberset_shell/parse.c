/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:57:28 by pberset           #+#    #+#             */
/*   Updated: 2024/06/24 15:00:00 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_solo.h"

char	**parse(char *input)
{
	char	**argv;

	argv = ft_split(input, ' ');
	if (!argv)
		return (NULL);
	return (argv);
}

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

void	init_cmd(t_commands *cmd, char *input, char **envp)
{
	cmd->envp = envp;
	cmd->argv = parse(input);
	if (!cmd->argv)
	{
		mega_free(cmd);
		return ;
	}
	cmd->path = get_path(envp);
	if (!cmd->path)
	{
		mega_free(cmd);
		return ;
	}
	cmd->exec_path = find_exec_path(cmd->argv[0], cmd->path);
	if (!cmd->exec_path)
	{
		mega_free(cmd);
		return ;
	}
}

size_t	count_pipes(char *input)
{
	size_t	count;

	count = 0;
	while (*input)
	{
		if (*input == '|')
			count++;
		input++;
	}
	return (count);
}