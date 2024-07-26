/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:14:28 by pberset           #+#    #+#             */
/*   Updated: 2024/07/26 18:59:11 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_cd(char **in, t_core *core)
{
	modifenv(findenv("OLDPWD"), ft_strdup(findenvvalue("PWD")));
	if (core->pipeline->param_count > 2)
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		return (1);
	}
	if (in[1] == NULL || !ft_strcmp(in[1], "~"))
	{
		if (chdir(core->env->home) < 0)
			return (1);
	}
	else if (core->pipeline->param_count == 2)
	{
		if (chdir(in[1]) < 0)
		{
			ft_printf_fd(2, "cd: ");
			perror(in[1]);
			return (1);
		}
	}
	modifenv(findenv("PWD"), ft_strdup(ms_getcwd()));
	return (0);
}
