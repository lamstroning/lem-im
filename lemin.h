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
# include <fcntl.h>
# define FD 3

typedef struct		s_map
{
	char			*name;
	int				type;
	int				empt;
	int				check;
	int				edge;
	int				step;
	struct s_cnt	*nbor;
}					t_map;
typedef struct		s_cnt
{
	struct s_map	*room;
	int				deep;
	struct s_cnt	*next;
}					t_cnt;

typedef struct		s_que
{
	struct s_que	*next;
	struct s_que	*prev;
	int				len;
	struct s_map	*way;
}					t_que;

typedef struct		s_date
{
	int				ants;
	char			**file;
	int				count;
	int				start;
	int				end;
}					t_date;

int					isroom(char *str);
void				getstr(t_date *conf);
int					dellist(char **str);
int					iscon(char *str);
int					isant(char *str, int i);
int					isvalid(t_date *conf);

void				count_rooms(t_date *conf);
int					inti_map(t_date *conf);
void				check_connect(char *line, t_map *rooms, int c);
void				output_way(t_que *que, int j);
t_map				create_room(t_map room);
int					connect_map(t_cnt **head, t_map *room);
t_cnt				*create_connect(t_map *rooms);
t_que				*make_que(t_map *pntr);

void				branchs_search(t_que **que, int count);
void				breadth_search(t_que **que, int j);
t_map				*next_lvl(t_map *pntr);

void				next_que(t_que **que, t_map *pntr, int check);
int					switch_next(t_map *pntr, t_que **que, int check);
int					long_way_up(t_que ***que, int check, int len);
int					prepare_room(t_map *rooms, t_date *conf);
int					end_search(t_map *pntr);
void				del_que(t_que **que);
void				switch_map(t_map **map, int order, t_que **que, int j);
void				tie_way(t_que **que, int check);
int					check_end(t_cnt **map, t_que **que, int check);
t_cnt				*roll_back(t_que **que);

// int					runnnig(t_que *que, t_date *conf);

# endif
