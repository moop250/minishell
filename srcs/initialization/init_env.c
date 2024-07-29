/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:43:24 by pberset           #+#    #+#             */
/*   Updated: 2024/07/28 14:46:21 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ms_get_env_paths(void)
{
	char	**paths;
	char	*temp;

	temp = findenvvalue("PATH");
	paths = ft_split(temp, ':');
	gfree(temp);
	return (paths);
}
