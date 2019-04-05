/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:31:47 by tdontos-          #+#    #+#             */
/*   Updated: 2019/03/30 18:31:49 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_map	create_room(t_map room)
{
	room.name = NULL;
	room.type = 0;
	room.check = 0;
	room.empt = 1;
	room.edge = 0;
	room.nbor = NULL;
	return (room);
}


int		connect_map(t_cnt **head, t_map *room)
{
	t_cnt	*tmp;

	if (head == NULL || *head == NULL || (*head)->room == NULL)
		*head = create_connect(room);
	else
	{
		tmp = *head;
		while ((*head)->next)
		{
			(*head)->deep++;
			if (room == (*head)->room || (*head)->next->room == room)
				return (0);
			*head = (*head)->next;
		}
		(*head)->deep++;
		(*head)->next = create_connect(room);
		*head = tmp;
	}
	return (1);
}

t_cnt	*create_connect(t_map *room)
{
	t_cnt *new;

	if (!(new = (t_cnt*)malloc(sizeof(t_cnt))))
		return (NULL);
	new->next = NULL;
	if (room != NULL)
		new->room = room;
	else
		new->room = NULL;
	new->deep = 0;
	return (new);
}
