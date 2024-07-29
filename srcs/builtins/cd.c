/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:14:28 by pberset           #+#    #+#             */
/*   Updated: 2024/07/29 11:02:52 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_cd(char **in, t_core *core)
{
	char	*tmp;

	modifenv(findenv("OLDPWD"), findenvvalue("PWD"));
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
	tmp = ms_getcwd();
	modifenv(findenv("PWD"), tmp);
	return (0);
}
