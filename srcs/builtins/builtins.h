/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:18:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/23 18:46:33 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

int		ms_cd(char **in, t_core *core);
int		ms_echo(char **in, t_core *core);
int		ms_env(char **in, t_core *core);
void	ms_exit(char **in, t_core *core);
int		ms_export(char **in, t_core *core);
int		ms_pwd(char **in, t_core *core);
int		ms_unset(char **in);

#endif
