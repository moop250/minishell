/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:20 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/24 16:15:52 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include "stdio.h"
# include "../libs/extended_ft/srcs/extended_ft.h"

// structs
typedef struct s_env
{
	char	*user_name;
	char	*hostname;
	char	**paths;
}	t_env;

typedef struct s_core
{
	struct s_env	*env;
	char			*current_dir;
}	t_core;

// functions
void	ms_error(char *in);
t_core	*init(int ac);

#endif