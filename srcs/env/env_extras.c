/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extras.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:19:00 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/24 17:35:30 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*findenvvalue(char *in)
{
	t_envparam	*env;

	env = findenv(in);
	if (env == NULL)
		return (ft_strdup(""));
	return (ft_strdup(env->value));
}
