/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:34:10 by tdontos-          #+#    #+#             */
/*   Updated: 2019/03/18 19:35:45 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# define FD 3

typedef struct		s_map
{
	char			*name;
	int				type;
	int				empt;
	int				check;
	int				edge;
	struct s_cnt	*nbor;
}			
					t_map;

typedef struct		s_cnt
{
	struct s_map	*room;
	int				deep;
	struct s_cnt	*next;
}
					t_cnt;

typedef struct		s_date
{
	int				ants;
	int				count;
	int				start;
	int				end;
}					t_date;

typedef struct		s_queue
{

}					t_queue;

t_map				*next_lvl(t_map room);
void				check_connect(char *line, t_cnt *conct, t_map *rooms, int c);
int					inti_map(t_date *conf, t_cnt *conct);
t_cnt				*create_connect(t_map *rooms);
int					connect_map(t_cnt **head, t_map *room);
t_cnt				*add_connect(t_cnt *head, t_map *add);
t_map				create_room(t_map room);
int					len_strct(t_map **nbr);
void				count_rooms(int fd, t_date *conf);
void				breadth_search(t_map room, t_date *conf);

# endif
