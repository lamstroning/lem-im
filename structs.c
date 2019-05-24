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
	room.check = -1;
	room.empt = 1;
	room.edge = 0;
	room.step = 0;
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
			{
				*head = tmp;
				return (0);
			}
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
	t_cnt	*new;

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

void	del_que(t_que **que)
{
	if (que == NULL || *que == NULL)
		return ;
	while ((*que)->prev != NULL)
	{
		(*que)->way->check = -1;
		(*que) = (*que)->prev;
		if ((*que)->next != NULL)
		{	
			free((*que)->next);
			(*que)->next = NULL;
		}
	}
	if ((*que)->way != NULL)
	(*que)->way->check = -1;
	free((*que)->next);
	free(*que);
	*que = NULL;
}

void	next_que(t_que **que, t_map *pntr, int check)
{
	if (*que == NULL)
		*que = ft_memalloc(sizeof(t_que));
	if ((*que)->next == NULL)
		(*que)->next = ft_memalloc(sizeof(t_que));
	else if (pntr == NULL || pntr->check != -1 ||
		((*que)->way != NULL && (*que)->way->type == 1))
		return ;
	(*que)->len++;
	if ((*que)->way != NULL)
	{
		(*que)->next->prev = *que;
		(*que) = (*que)->next;
	}
	(*que)->way = pntr;
	(*que)->way->check = pntr->type == 1 ? -1 : check;
	if (pntr->type != 1)
		(*que)->next = (t_que *)ft_memalloc(sizeof(t_que));
}
