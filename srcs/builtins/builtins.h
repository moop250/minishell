/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:18:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/17 16:21:29 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

void	ms_unset(char **in, t_core *core);
void	ms_env(char **in, t_core *core);
void	ms_export(char **in, t_core *core);
void	ms_echo(char **in, t_core *core);
void	ms_pwd(char **in, t_core *core);
void	ms_exit(t_core *core, char **in);

#endif
