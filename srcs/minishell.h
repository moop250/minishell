/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:08:20 by hlibine           #+#    #+#             */
/*   Updated: 2024/07/30 18:00:34 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// includes
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include "../libs/extended_ft/srcs/extended_ft.h"

// Default Variables
# define DEF_PROMPT "\033[35m"
# define CLEAR "\033[0m"
# define ORANGE "\033[38;5;208m"

# define QUOTES "\"\'"
# define REDIRECTS "<>|"
# define WHITESPACE " \n\t"

# define NOENVPATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

// Error Messages
# define GENERROR "minishell error:"
# define PARSEERROR "parse error near"
# define QUOTEERROR "incomplete quote of type"
# define TOOMANY "too many arguments"
# define WHYLETTER "numeric argument required"

// structs
typedef struct s_pipe_fd
{
	bool				append;
	bool				heredoc;
	char				*file_name;
	int					fd;
	struct s_pipe_fd	*next;
	struct s_pipe_fd	*prev;
}						t_pipe_fd;

typedef struct s_pipeline
{
	char				**params;
	int					param_count;
	bool				heredoc;
	struct s_pipe_fd	*pipeline_in;
	struct s_pipe_fd	*pipeline_out;
	struct s_pipeline	*next;
	struct s_pipeline	*prev;
}						t_pipeline;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
}	t_token;

typedef struct s_envparam
{
	bool				base;
	char				*name;
	char				*value;
	struct s_envparam	*next;
	struct s_envparam	*prev;
}						t_envparam;

typedef struct s_env
{
	t_envparam	*rawenvs;
	bool		hasenv;
	char		*user;
	char		*home;
	char		*hostname;
	char		**paths;
	char		**envp;
	char		*cwd;
}	t_env;

typedef struct s_core
{
	int				argc;
	char			**argv;
	t_env			*env;
	char			*current_dir;
	char			*prompt;
	char			*line;
	t_token			*token;
	int				pipe_count;
	int				token_count;
	t_pipeline		*pipeline;
	int				exit_status;
}	t_core;

// functions
void		ms_error(char *in);
void		ms_printerror(int errorcode, char *in);
void		exec_err(int *pipe_fd, char *execp, char *msg);
t_core		*init(int ac, char **av, char **env);
int			tokenizer(char *input, t_core *core);
t_core		*minishell_loop(int ac, char **av, char **env);
void		addenvend(t_core *core, char *in, bool env);
t_envparam	*findenv(const char *name);
void		modifenv(t_envparam *env, char *str);
t_core		*get_core(void);
void		init_envs(t_core *core, char **env);
void		init_noenv(t_core *core);
void		fill_core_env(t_core *core);
void		clear_envs(t_envparam *envs);
char		*ms_getcwd(void);
void		parser(t_core *core, t_token *token);
char		*findenvvalue(char *in);
char		**ms_get_env_paths(void);
void		ms_freeall(t_core *core);
void		ms_update(t_core *core);
t_envparam	*ms_cust_addenvend(t_envparam *param,
				char *name, char	*value, bool env);

// execution
int			execute(t_core *core);
int			execute_one(t_core *core);
int			is_builtin(char *cmd);
int			execute_builtins(t_core *core);
int			init_pipes(t_pipeline *cmd, int pipes[2][2], int i, int pipe_count);
int			handle_redirections(t_pipeline *cmd);
int			handle_files(t_pipeline *pipeline);
int			handle_infile(t_pipe_fd *p_in);
int			handle_heredoc(t_pipe_fd *p_in);
int			handle_outfile(t_pipe_fd *p_out);
char		*init_execp(t_pipeline *current, char **paths);
void		signal_handler(int signal);

#endif
