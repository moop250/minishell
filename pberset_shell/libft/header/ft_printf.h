/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:31:47 by pberset           #+#    #+#             */
/*   Updated: 2023/12/05 19:58:15 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

// 42 printf %(c, s, p, d, i, u, x, X, %)
int	ft_printf(const char *format, ...);
// Writes unsigned int to the file descriptor
int	ft_putuint_fd(unsigned int n, int fd);
// Writes lowercase (0) or uppercase (1) hexadecimal conversion of int
int	ft_puthex_fd(unsigned long n, int up, int fd);
// Writes hex value of the address of a void *
int	ft_putptr_fd(void *p, int fd);
// Tests if the input character is a space
int	ft_isspace(char c);

#endif
