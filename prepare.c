/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:33:21 by tdontos-          #+#    #+#             */
/*   Updated: 2019/04/15 11:33:25 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		prepare_room(t_map *rooms, t_date *conf)
{
	t_cnt	*pntr;
	t_que	**que;
	t_map	*begin;
	int		i;
	int		j;

	if (rooms[conf->end].edge > rooms[conf->start].edge)
	{
		begin = &rooms[conf->start];
		ft_swap(&rooms[conf->end].type, &begin->type);
	}
	else
		begin = &rooms[conf->end];
	begin->check = 1;
	i = begin->edge  * 2 + 2;
	pntr = begin->nbor;
	j = begin->edge;
	que = (t_que**)ft_memalloc(sizeof(t_que*) * j);
	while (j > 0)
	{
		j--;
		que[j] = (t_que*)ft_memalloc(sizeof(t_que));
		next_que(&que[j], &rooms[conf->start], j);
		next_que(&que[j], pntr->room, j);
		pntr = pntr->next;
	}
	pntr = begin->nbor;
	while (i--)
	{
		breadth_search(&que[j], j);
		if (que[j] != NULL && que[j]->way->type == 1)
			output_way(que[j],j);
		j = j + 1 >= begin->edge ? 0 : j + 1;
		if ((pntr = pntr->next) == NULL)
		{
			branchs_search(que, begin->edge + 1);
			pntr = begin->nbor;
		}
	}
	// runnnig(*que, *conf);
	return(1);
}

void	branchs_search(t_que **que, int count)
{
	int		tie[count];
	t_que	**p_que;
	int		i;

	i = 0;
	p_que = que;
	while (i < count - 1)
	{
		if (p_que[i]->way->type != 1)
			tie[i] = 0;
		else
			tie[i] = -1;
		i++;
	}
	while(--i > -1)
	{
		if (tie[i] == 0)
			tie_way(&que[i], i);
	}
}

void	tie_way(t_que **que, int check)
{
	t_que	**p_que;
	t_cnt	*n;
	int		i;
	int		q;

	i = (*que)->way->edge;
	p_que = (t_que **)ft_memalloc(sizeof(t_que*) * i - 1);
	while (--i > -1)
		p_que[i] = (t_que *)ft_memalloc(sizeof(t_que));
	n = (*que)->way->nbor;
	while (n != NULL)
	{
		if (n->room->check == -1)
		{
			i++;
			next_que(&p_que[i], n->room, check);
			p_que[i]->len = (*que)->len + 1;
		}
		n = n->next;
	}
	if (i >= 0)
	{
		q = long_way_up(&p_que, check, i);
		if (q != -1)
		{
			free((*que)->next);
			while (p_que[q]->prev != NULL)
				p_que[q] = p_que[q]->prev;
			p_que[q]->prev = *que;
			(*que)->next = p_que[q];
		}
	}
	i = 0;
	while (i < (*que)->way->edge)
	{
		if (i == q)
		{
			if (i + 1 < (*que)->way->edge)
				i++;
			else
				break ;
		}
		del_que(&p_que[i++]);
	}
	while ((*que)->next != NULL && q != -1)
		*que = (*que)->next;
}

int		long_way_up(t_que ***p_que, int check, int len)
{
	int		i;
	int		end[len + 1];
	t_cnt	*n;

	i = len + 1;
	while (--i > -1)
		end[i] = 0;
	while (1)
	{
		if (i > len || i < 0)
			i = 0;
		if ((*p_que)[i] == NULL || end[i] == 1)
		{
			i = 0;
			while ((*p_que)[i]->way == NULL || end[i] == 1)
			{
				if (i > len)
					return (-1);
				i++;
			}
		}
		n = (*p_que)[i]->way->nbor;
		while (n != NULL)
		{
			if (n->room->check == -1)
			{
				next_que(&(*p_que)[i], n->room, check);
				if (check_end(&n, &(*p_que)[i], check) == 1)
					return (i);
				i++;
				break ;
			}
			n = n->next;
			if (n == NULL)
			{
				n = roll_back(&(*p_que)[i]);
				end[i] = n == NULL ? 1 : 0; 
				i++;
			}
		}
	}
	return (-1);
}

t_cnt	*roll_back(t_que **que)
{
	t_cnt	*n;


	while (*que != NULL)
	{
		n = (*que)->way->nbor;
		while (n != NULL)
		{
			if (n->room->check == -1)
				return (n);
			n = n->next;
		}
		(*que)->way->check = -1;
		free((*que)->next);
		(*que)->next = NULL;
		if ((*que)->prev == NULL)
			return (NULL);
		*que = (*que)->prev;
	}
	return (NULL);
}

int		check_end(t_cnt **map, t_que **que, int check)
{
	t_cnt	*next;

	next = *map;
	while (next != NULL)
	{
		if (next->room->type == 1)
		{
			if ((*que)->way->type != 1)
				next_que(que, next->room, check);
			return (1);
		}
		next = next->next;
	}
	return (0);
}

void	output_way(t_que *que, int j)
{
	static int end[10];

	if (end[j] == 1)
		return ;
	ft_printf("\n_____%d_____\n", j);
	while (que)
	{
		end[j] = 1;
		ft_printf("%s\n",que->way->name);
		que = que->prev;
	}
}
