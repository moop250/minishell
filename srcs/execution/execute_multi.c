/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:11:37 by pberset           #+#    #+#             */
/*   Updated: 2024/07/14 18:17:32 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_other_pipes(int **pipefd, int i, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		if (j != i - 1 && j != i)
		{
			if (close(pipefd[j][0]) < 0)
			{
				exec_err(pipefd[j], NULL, "close pipefd[j][0]");
				exit(EXIT_FAILURE);
			}
			if (close(pipefd[j][1]) < 0)
			{
				exec_err(pipefd[j], NULL, "close pipefd[j][1]");
				exit(EXIT_FAILURE);
			}
		}
		j++;
	}
}

void execute_multi(int cmd_count, t_pipeline *pipeline, char **paths, char **env)
{
    int         **pipefd;
    int         i;
    pid_t       *pid;
    t_pipeline  *current;
    int         status;

    pipefd = (int **)ft_calloc(cmd_count - 1, sizeof(*pipefd));
    if(!pipefd)
    {
        exec_err(NULL, NULL, "ft_calloc");
        return;
    }
    i = 0;
    while (i < cmd_count - 1) {
        pipefd[i] = (int *)ft_calloc(2, sizeof(int));
        if (pipe(pipefd[i]) < 0)
        {
            exec_err(NULL, NULL, "pipe");
            return;
        }
        i++;
    }
    current = pipeline;
    pid = (pid_t *)ft_calloc(cmd_count, sizeof(pid_t));
    i = 0;
    while (i < cmd_count)
    {
        pid[i] = fork();
        if (pid[i] < 0)
        {
            exec_err(NULL, NULL, "fork");
            return;
        }
        if (pid[i] == 0)
        {
            // First command
            if (i == 0 && cmd_count > 1)
            {
                dup2(pipefd[0][1], STDOUT_FILENO);
            }
            // Middle commands
            else if (i < cmd_count - 1)
            {
                dup2(pipefd[i-1][0], STDIN_FILENO);
                dup2(pipefd[i][1], STDOUT_FILENO);
            }
            // Last command
            else if (i == cmd_count - 1 && i > 0)
            {
                dup2(pipefd[i-1][0], STDIN_FILENO);
            }

            // Close all pipe fds in child
            int j = 0;
            while (j < cmd_count - 1)
            {
                close(pipefd[j][0]);
                close(pipefd[j][1]);
                j++;
            }

            current->execp = init_execp(current, paths);
            execve(current->execp, current->params, env);
            exec_err(NULL, current->execp, current->params[0]);
            exit(EXIT_FAILURE);
        }
        current = current->next;
        i++;
    }

    // Parent process
    // Close all pipe fds in parent
    i = 0;
    while (i < cmd_count - 1)
    {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
        free(pipefd[i]);
        i++;
    }
    free(pipefd);

    // Wait for all child processes
    i = 0;
    while (i < cmd_count)
    {
        waitpid(pid[i], &status, 0);
        i++;
    }
    free(pid);
}
