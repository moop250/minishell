/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:20 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/23 16:38:43 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include "stdio.h"
# include "../libs/extended_ft/srcs/extended_ft.h"

// structs
typedef struct s_core
{
	char **env;
	char **current_dir;
}	t_core;

// functions
void	ms_error(char *in);
t_core	*init(int ac);

#endif