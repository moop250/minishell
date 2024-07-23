/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:48:11 by pberset           #+#    #+#             */
/*   Updated: 2024/07/23 18:56:19 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Change  the  current  directory  to  dir.
 *
 * If dir is not supplied, the value of the HOME shell variable is the default.
 *
 * The variable CDPATH defines the search path for the  directory  containing dir:
 * each directory name in CDPATH is searched for dir.
 *
 * Alternative directory names in CDPATH are separated by a colon (:).
 *
 * A null directory name in CDPATH is the same as the current directory, i.e., ``.''.
 *
 * If dir begins with a slash (/), then CDPATH is not used.
*/
 #include "builtins.h"

 int	ms_cd(char **in, t_core *core)
 {
	(void)core;
 	if (!ft_strcmp(in[1], ".."))
		if (chdir(in[1]) < 0)
			return (1);
	if (!ft_strcmp(in[1], "."))
		return (0);
	if (!ft_strcmp(in[1], "~"))
	{
		if (chdir("/Users/pberset") < 0)
			return (1);
	}
	return (0);
 }