/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:54:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/21 22:11:36 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	env_sorter(char **envs, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len - 1 - i)
			if (ft_strcmp(envs[j], envs[j + 1]) > 0)
			{
				tmp = ft_strdup(envs[j]);
				gfree(envs[j]);
				envs[j] = envs[j + 1];
				envs[j + 1] = tmp;
			}
	}
}

static void	print_export(t_core *core)
{
	char		**sorted_list;
	t_envparam	*tmp;
	size_t		i;

	tmp = core->env->rawenvs;
	i = 0;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	sorted_list = galloc((i + 1) * sizeof(char *));
	tmp = core->env->rawenvs;
	i = -1;
	while (tmp)
	{
		sorted_list[++i] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	sorted_list[i] = NULL;
	env_sorter(sorted_list, i);
	i = -1;
	while (sorted_list[++i])
		ft_printf_fd(core->ms_stdout, "declare -x %s\n", sorted_list[i]);
	ft_2dfree((void **)sorted_list);
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
