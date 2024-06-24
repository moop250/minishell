/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:29:32 by pberset           #+#    #+#             */
/*   Updated: 2024/03/14 14:23:02 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow10(int pow)
{
	int	output;

	output = 1;
	while (pow)
	{
		output *= 10;
		pow--;
	}
	return (output);
}