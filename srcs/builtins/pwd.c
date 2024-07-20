/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:56:52 by pberset           #+#    #+#             */
/*   Updated: 2024/07/20 11:14:39 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_pwd(char **in, t_core *core)
{
	char	*tmp;

	if (in[1])
	{
		ms_printerror(3, NULL);
		core->exit_status = 1;
		return ;
	}
	tmp = ms_getcwd();
	ft_printf_fd(core->ms_stdout, "%s\n", tmp);
	gfree(tmp);
	core->exit_status = 0;
}
