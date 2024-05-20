/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collecter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:30:51 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/20 15:23:33 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

static bool	free_from_ll(void *address)
{
	t_garbcol	*todel;

	todel = *getgarbage();
	while (todel && address)
	{
		if (todel->content == address)
		{
			if (todel->previous)
			{
				todel->previous->next = todel->next;
				todel->next->previous = todel->previous;
			}
			else
			{
				todel->next->previous = 0;
				*getgarbage() = todel->next;
			}
			free(todel->content);
			free(todel);
			return (true);
		}
		todel = todel->next;
	}
	return (false);
}

//frees a specific address malloced by galloc
void	gfree(void *address)
{
	if (address && !GARBAGE_COLLECTOR)
		free(address);
	else if (!address || !GARBAGE_COLLECTOR)
		return ;
	else if (!free_from_ll(address))
		free(address);
}

void	*addgarbage(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*tmp;

	if (!address)
		return (0);
	collector = getgarbage();
	tmp = (t_garbcol *)malloc(sizeof(t_garbcol));
	if (!tmp)
		return (0);
	tmp->next = 0;
	tmp->previous = 0;
	tmp->content = address;
	if (*collector)
	{
		tmp->next = *collector;
		tmp->next->previous = tmp;
		*collector = tmp;
	}
	else
		*collector = tmp;
	return (tmp->content);
}

//graciously stolen from https://github.com/RPDJF/
void	*galloc(size_t size)
{
	return (addgarbage(malloc(size)));
}

//clears all garbage malloced with galloc
void	razegarbage(void)
{
	t_garbcol	**collector;
	t_garbcol	*todel;
	t_garbcol	*tmp;

	collector = getgarbage();
	todel = *collector;
	while (todel)
	{
		free(todel->content);
		tmp = todel->next;
		free(todel);
		todel = tmp;
	}
	*collector = 0;
}
