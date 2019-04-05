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

void	breadth_search(t_map room, t_date *conf)
{
	t_map	*pntr;

	pntr = &room;
	while (pntr->nbor->room)
	{
		if (pntr->check != 1)
			pntr->check = 1;
		pntr = next_lvl(*pntr);
	}
}

t_map	*next_lvl(t_map room)
{
	t_map	*pntr;
	t_map	root;
	t_map	*next;
	int		i;

	next = NULL;
	i = 0;
	root = room;
	pntr = &room;
	while (pntr->nbor != NULL)
	{
		if (pntr->nbor->room->type == 2)
		{
			ft_printf("%s\n", pntr->nbor->room->name);
				exit(1);
		}
		if (next == NULL && pntr->nbor->room->check == 0)
			next = pntr->nbor->room;
		if (pntr->nbor->next != NULL)
			pntr->nbor = pntr->nbor->next;
		else
			break ;
		i++;
	}
	if (next == NULL)
	{
		ft_printf("Sorry, I'm can't search way, please check, again");
		exit(1);
	}
	return (next);
}
