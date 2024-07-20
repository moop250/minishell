/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:54:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/20 11:27:40 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**env_sorter(t_envparam *env)
{
	t_envparam	*tmp;
	char		**out;

	return (out);
}

static void	print_export(t_core *core)
{
	char	**sorted_in;
	size_t	i;

	i = -1;
	sorted_in = env_sorter(core->env->rawenvs);
	while (sorted_in[++i])
		ft_printf_fd(core->ms_stdout, "declare -x %s\n", sorted_in[i]);
	i = -1;
	ft_2dfree((void **)sorted_in);
}

void	ms_export(char **in, t_core *core)
{
	size_t		i;
	t_envparam	*param;

	i = 0;
	if (in[1] == NULL)
		print_export(core);
	while (in[++i])
	{
		param = findenv(in[i]);
		if (!param)
			addenvend(core, in[i], false);
		else
		{
			gfree(param->value);
			param->value = ft_strdup(in[i]);
		}
	}
	core->exit_status = 0;
}
