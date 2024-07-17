/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:54:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/17 17:20:00 by hlibine          ###   ########.fr       */
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
	ft_2dfree(sorted_in);
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
