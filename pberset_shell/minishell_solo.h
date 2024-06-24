/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_solo.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:50:11 by pberset           #+#    #+#             */
/*   Updated: 2024/06/24 15:00:25 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SOLO_H
# define MINISHELL_SOLO_H

# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft/header/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_CMD_LEN 1024
# define PROMPT "minishell$ "

typedef struct s_commands
{
	char	**argv;
	char	**envp;
	char	**path;
	char	*exec_path;
	size_t	pipe_count;
}	t_commands;

void	shell(char *input, char **envp);
void	init_cmd(t_commands *cmd, char *input, char **envp);
void	mega_free(t_commands *cmd);
void	execute(t_commands *cmd);
char	**parse(char *input);
char	*find_exec_path(char *cmd, char **path);
char	**get_path(char **envp);
size_t	count_pipes(char *input);

#endif