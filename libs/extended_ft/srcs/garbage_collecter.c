/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collecter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:30:51 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:19:19 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

t_garbcol	**getgarbage(void)
{
	static t_garbcol	*collector;

	return (&collector);
}

//frees a specific address malloced by galloc
void	gfree(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*todel;

	collector = getgarbage();
	todel = *collector;
	while (todel && todel->content != address)
		todel = todel->next;
	if (!todel)
		free(address);
	else
	{
		if (todel->previous)
			todel->previous->next = todel->next;
		else
			*collector = todel->next;
		if (todel->next)
			todel->next->previous = todel->previous;
		free(todel->content);
		free(todel);
	}
}

void	*addgarbage(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*tmp;
	t_garbcol	*last;

	if (!address)
		return (0);
	collector = getgarbage();
	tmp = (t_garbcol *)malloc(sizeof(t_garbcol));
	if (!tmp)
		return (0);
	last = 0;
	tmp->next = 0;
	tmp->previous = 0;
	tmp->content = address;
	if (*collector)
	{
		last = lastgarbage(*collector);
		last->next = tmp;
		tmp->previous = last;
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
