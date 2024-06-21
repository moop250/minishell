/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:49:48 by pberset           #+#    #+#             */
/*   Updated: 2024/06/21 09:06:48 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_solo.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1 || !envp)
	{
		ft_printf("Error: args or no environment\n");
		return (1);
	}
	(void)argv;
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (strlen(input) > 0)
		{
			add_history(input);
			shell(input, envp);
		}
		free(input);
		input = NULL;
	}
	return (0);
}
