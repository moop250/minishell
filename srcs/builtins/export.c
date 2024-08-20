/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:54:21 by pberset           #+#    #+#             */
/*   Updated: 2024/08/08 13:10:20 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	swap_nodes(t_envparam *a, t_envparam *b)
{
	char	*tmp;

	tmp = a->name;
	a->name = b->name;
	b->name = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

static void	env_sorter(t_envparam *envs)
{
	int			swapped;
	t_envparam	*ptr;
	t_envparam	*lptr;

	if (!envs)
		return ;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = envs;
		while (ptr->next != lptr)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				swap_nodes(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr;
	}
}

static void	print_export(t_core *core)
{
	t_envparam	*tmp;
	t_envparam	*copy;

	copy = NULL;
	tmp = core->env->rawenvs;
	while (tmp)
	{
		copy = ms_cust_addenvend(copy, tmp->name, tmp->value, true);
		tmp = tmp->next;
	}
	env_sorter(copy);
	tmp = copy;
	while (tmp)
	{
		if (tmp->value)
			ft_printf_fd(STDOUT_FILENO, "declare -x %s=\"%s\"\n",
				tmp->name, tmp->value);
		else
			ft_printf_fd(STDOUT_FILENO, "declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	clear_envs(copy);
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
			addenvend(core, in[i], false);
		else
		{
			if (in[i][ft_strlen(in[i]) - 1] == '=')
				modifenv(param, ft_strdup(""));
			else if (!tmp[1])
				modifenv(param, NULL);
			else
				modifenv(param, ft_strdup(tmp[1]));
		}
		ft_2dfree((void **)tmp);
	}
	return (0);
}
