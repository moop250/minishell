/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:18:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/26 18:52:27 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

int		ms_cd(char **in, t_core *core);
int		ms_echo(char **in);
int		ms_env(char **in, t_core *core);
void	ms_exit(char **in, t_core *core);
int		ms_export(char **in, t_core *core);
int		ms_pwd(char **in, t_core *core);
int		ms_unset(char **in);

#endif
