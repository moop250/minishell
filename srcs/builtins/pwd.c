/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:56:52 by pberset           #+#    #+#             */
/*   Updated: 2024/07/24 14:23:40 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_pwd(char **in, t_core *core)
{
	char	*tmp;

	(void)core;
	if (in[1])
	{
		ms_printerror(3, NULL);
		return (1);
	}
	tmp = ms_getcwd();
	ft_printf_fd(STDOUT_FILENO, "%s\n", tmp);
	gfree(tmp);
	return (0);
}
