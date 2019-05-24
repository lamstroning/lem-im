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


int		init_map(t_date *conf)
{
	int		i;
	int		j;
	t_map	*rooms;

	i = 0;
	j = -1;
	rooms = (t_map*)ft_memalloc(sizeof(t_map) * conf->count);
	while (conf->file[++j] != NULL)
	{
		if (conf->file[j][0] == '#' && conf->file[j][1] != '#')
			continue ;
		if (rooms[i].name == NULL && i < conf->count)
			rooms[i] = create_room(rooms[i]);
		if (ft_strcmp(conf->file[j], "##start") == 0)
			rooms[i].type = 1;
		else if (ft_strcmp(conf->file[j], "##end") == 0)
			rooms[i].type = 2;
		if (i < conf->count && rooms[i].type != 0)
			j++;
		if (ft_strchr(conf->file[j], ' ') != NULL)
			rooms[i++].name = ft_strcpy_chr(conf->file[j], ' ');
		else if (ft_strchr(conf->file[j], '-') != NULL)
			check_connect(conf->file[j], rooms, conf->count);
	}
	prepare_room(rooms, conf);
	return (1);
}

void	check_connect(char *line, t_map *rooms, int c)
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

void	count_rooms(t_date *conf)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	conf->ants = ft_atoi(conf->file[0]);
	while (conf->file[++i] != NULL)
	{
		if (ft_strcmp(conf->file[i], "##start") == 0)
			conf->start = count;
		else if (ft_strcmp(conf->file[i], "##end") == 0)
			conf->end = count;
		if (conf->file[i][0] == '#' || ft_strchr(conf->file[i], ' ') == NULL)
			continue ;
		count++;
	}
	conf->count = count;
}

int		main(void)
{
	t_date	*conf;
	int		fd;

	fd = open("/Users/tdontos-/Desktop/lem-in/wtf", O_RDONLY);
	conf = (t_date*)ft_memalloc(sizeof(t_date));
	getstr(conf);
	count_rooms(conf);
	if (!init_map(conf))
		exit(1);
	dellist(conf->file);
	return (0);
}
