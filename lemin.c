/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdontos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:11:21 by tdontos-          #+#    #+#             */
/*   Updated: 2019/03/18 19:11:22 by tdontos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <fcntl.h>

int		init_map(t_date *conf, t_cnt *conct)
{
	int		i;
	char	*line;
	t_map	*rooms;
	i = 0;

	rooms = (t_map*)ft_memalloc(sizeof(t_map) * conf->count);
	while (get_next_line(FD, &line) > 0)
	{
		if (line[0] == '#' && line[1] != '#')
				continue ;
			if (rooms[i].name == NULL && i < conf->count)
				rooms[i] = create_room(rooms[i]);
			if (ft_strcmp(line, "##start") == 0)
				rooms[i].type = 1;
			else if (ft_strcmp(line, "##end") == 0)
				rooms[i].type = 2;
			if (i < conf->count && rooms[i].type != 0)
				get_next_line(FD, &line);
		if (ft_strchr(line, ' ') != NULL)
			rooms[i++].name = ft_strcpy_chr(line, ' ');
		else if (ft_strchr(line, '-') != NULL)
			check_connect(line, conct, rooms, conf->count);
	}
	ft_strdel(&line);
	breadth_search(rooms[conf->start], conf);
	while (i > 0)
		ft_printf("%s\n", rooms[--i].name);
	return (1);
}

void		check_connect(char *line, t_cnt *conct, t_map *rooms, int c)
{
	char	*frst;
	char	*scnd;
	int		f;
	int		s;
	int		i;

	s = -1;
	f = -1;
	i = -1;
	if (line[0] == '-')
		return ;
	frst = ft_strcpy_chr(line, '-');
	scnd = ft_strdup(ft_strchr(line, '-') + 1);
	while (++i < c)
	{
		if (ft_strcmp(frst, rooms[i].name) == 0)
			f = i;
		if (ft_strcmp(scnd, rooms[i].name) == 0)
			s = i;
		if (f != -1 && s != -1)
			break ;
	}
	if (f == -1 || s == -1 || f == s)
		return ;
	rooms[f].edge += connect_map(&rooms[f].nbor, &rooms[s]);
	rooms[s].edge += connect_map(&rooms[s].nbor, &rooms[f]);
}

void	count_rooms(int fd, t_date *conf)
{
	int		count;
	char	*line;

	count = 0;
	get_next_line(FD, &line);
	if (line != NULL)
		conf->ants = ft_atoi(line);
	if (conf->ants <= 0)
		exit(1);
	while (get_next_line(FD, &line) > 0)
	{
		if (ft_strcmp(line, "##start") == 0)
			conf->start = count;
		else if (ft_strcmp(line, "##end") == 0)
			conf->end = count;
		if (line[0] == '#' || ft_strchr(line, ' ') == NULL)
			continue ;
		count++;
	}
	conf->count = count;
	close(fd);
	fd = open("map", O_RDONLY);
	ft_strdel(&line);
}

int		main(void)
{
	int		fd;
	t_date	*conf;
	t_cnt	*conct;
	conct = NULL;

	fd = open("map", O_RDONLY);
	conf = (t_date*)ft_memalloc(sizeof(t_date));
	count_rooms(fd, conf);
	if (!init_map(conf, conct))
		exit(1);
	return (0);
}
