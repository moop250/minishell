/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:06:33 by hlibine           #+#    #+#             */
/*   Updated: 2024/04/30 08:14:28 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_printerror(char *in)
{
	ft_putstr_fd("\033[1;31mminishell error: ", 2);
	ft_putstr_fd(in, 2);
	ft_putendl_fd("\033[0m", 2);
}

void	ms_error(char *in)
{
	ms_printerror(in);
	razegarbage();
	exit(EXIT_FAILURE);
}