/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:06:33 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/15 16:51:31 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_printerror(char *in)
{
	ft_printf_fd(2, "\033[1;31mminishell error: %s\033[0m", in);
}

void	ms_error(char *in)
{
	ft_printf_fd(2, "\033[1;31mminishell error: %s\033[0m", in);
	razegarbage();
	exit(EXIT_FAILURE);
}