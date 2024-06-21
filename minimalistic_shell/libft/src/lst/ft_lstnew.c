/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:27:24 by pberset           #+#    #+#             */
/*   Updated: 2024/03/18 14:30:28 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*output;

	output = (t_list *)malloc(sizeof(t_list));
	if (!output)
		return (NULL);
	output->content = (void *)malloc(sizeof(content));
	if (!output->content)
	{
		free(output);
		return (NULL);
	}
	ft_memcpy(output->content, content, sizeof(content));
	output->next = NULL;
	return (output);
}
