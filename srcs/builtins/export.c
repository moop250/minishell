/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:54:21 by pberset           #+#    #+#             */
/*   Updated: 2024/07/25 15:04:18 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	env_sorter(char **envs, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = -1;
	envs[len] = NULL;
	while (++i < len)
	{
		j = -1;
		while (++j < len - 1 - i)
		{
			if (ft_strcmp(envs[j], envs[j + 1]) > 0)
			{
				tmp = ft_strdup(envs[j]);
				gfree(envs[j]);
				envs[j] = envs[j + 1];
				envs[j + 1] = tmp;
			}
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
	env_sorter(sorted_list, i);
	i = -1;
	while (sorted_list[++i])
		ft_printf_fd(STDOUT_FILENO, "declare -x %s=\"%s\"\n",
			sorted_list[i], findenvvalue(sorted_list[i]));
	ft_2dfree((void **)sorted_list);
}

int	ms_export(char **in, t_core *core)
{
	size_t		i;
	t_envparam	*param;
	char		**tmp;

	i = 0;
	if (in[1] == NULL)
		print_export(core);
	while (in[++i])
	{
		tmp = ft_split(in[i], '=');
		param = findenv(tmp[0]);
		if (!param)
		{
			if (!tmp[1])
				addenvend(core, in[i], false);
			else
				addenvend(core, in[i], true);
		}
		else
			modifenv(param, ft_strdup(tmp[1]));
		ft_2dfree((void **)tmp);
	}
	return (0);
}
