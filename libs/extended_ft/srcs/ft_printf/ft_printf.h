/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:11:10 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/15 14:06:03 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../extended_ft.h"

void	ft_printf_putnbr(int n, char *str, int *p, int fd);
void	ft_printf_ptohex(void *p, int *o, int fd);
void	ft_printf_putchar(char c, int *p, int fd);
void	ft_printf_putstr(char *str, int *p, int fd);
void	ft_printf_putnbrun(unsigned long int n, char *str, int *p, int fd);

#endif