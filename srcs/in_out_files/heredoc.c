#include "../minishell.h"

void	handle_heredoc(t_pipe_fd *pipeline_in)
{
	char	*input;
	int		fd[2];

	input = "";
	pipe(fd);
	pipeline_in->fd = dup(STDIN_FILENO);
	while (42)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strcmp(input, pipeline_in->file_name) == 0)
		{
			free(input);
			input = NULL;
			break ;
		}
		ft_printf_fd(fd[1], "%s", input);
		free(input);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
