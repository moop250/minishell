/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:56:52 by pberset           #+#    #+#             */
/*   Updated: 2024/07/16 14:25:51 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_pwd(t_core *core)
{
	char	*tmp;

	tmp = ms_getcwd();
	ft_printf_fd(core->ms_stdout, "%s\n", tmp);
	gfree(tmp);
	core->exit_status = 0;
}
