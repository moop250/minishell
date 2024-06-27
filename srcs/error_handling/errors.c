/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:06:33 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/27 17:01:07 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Error Codes:
0 = General error. in will be a custom message
1 = Parsing error. in will be the erronious character
*/
void	ms_printerror(int errorcode, char *in)
{
	ft_printf_fd(2, "\033[1;31m");
	if (errorcode == 0)
		ft_printf_fd(2, "%s %s", GENERROR, in);
	else if (errorcode == 1)
		ft_printf_fd(2, "%s %s '%s'", GENERROR, PARSEERROR, in);
	ft_printf_fd(2, "\033[0m\n");
}

void	ms_error(char *in)
{
	ft_printf_fd(2, "\033[1;31mminishell error: %s\033[0m", in);
	razegarbage();
	exit(errno);
}
