/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:43:24 by pberset           #+#    #+#             */
/*   Updated: 2024/07/29 23:33:43 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_getcwd(void)
{
	char	*result;
	char	path[PATH_MAX];

	result = NULL;
	result = getcwd(result, sizeof(path));
	if (!result)
		ms_error("getcwd error");
	addgarbage(result);
	return (result);
}

char	**ms_get_env_paths(void)
{
	char	**paths;
	char	*temp;

	temp = findenvvalue("PATH");
	paths = ft_split(temp, ':');
	gfree(temp);
	return (paths);
}
