/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:18:17 by tdontos-          #+#    #+#             */
/*   Updated: 2019/03/25 17:18:18 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	breadth_search(t_que **que, int j)
{
	t_map	*map;

	if ((*que)->way->type == 1)
		return ;
	map = (*que)->way;
	switch_map(&map, 2, que, j);
	while (map->nbor != NULL && map->nbor->next != NULL)
	{
		if (map->type == 1)
		{
			next_que(que, map, j);
			return ;
		}
		if (map->edge == 2)
			switch_map(&map, 1, que, j);
		else if (map->edge > 2)
		{
			if (switch_next(map, que, j) == 1)
				map = (*que)->way;
			else
				return ;
		}
	}
}

void	switch_map(t_map **map, int order, t_que **que, int j)
{
	t_cnt	*head;
	t_map	*next;

	head = (*map)->nbor;
	next = NULL;
	if (order == 1)
		next_que(que, *map, j);
	while (head != NULL)
	{
		if (head->room->check == -1)
		{
			if (next == NULL)
				next = head->room;
			else
				return ;
		}
		head = head->next;
	}
	if (next == NULL)
	{
		(*map)->nbor = NULL;
		return ;
	}
	*map = next;
	if (order == 0)
		next_que(que, *map, j);
}

int		switch_next(t_map *pntr, t_que **que, int check)
{
	t_cnt	*map;
	t_map	*tmp;

	map = pntr->nbor;
	tmp = NULL;
	while (map != NULL)
	{
		if (map->room->type == 1)
		{
			next_que(que, pntr, check);
			next_que(que, map->room, check);
			return (0);
		}
		if (tmp != NULL && map->room->check == -1)
			return (0);
		if (map->room->check == -1 || map->room->type == 1)
			tmp = map->room;
		map = map->next;
	}
	if (tmp == NULL)
		return (0);
	next_que(que, tmp, check);
	return (1);
}

