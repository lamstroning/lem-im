/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate-map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:49:07 by kmurch            #+#    #+#             */
/*   Updated: 2019/05/14 19:28:05 by kmurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int getcells(char **str)
{
	int     x;
	int     cells;

	cells = 0;
	x = -1;
	while (str[++x])
		if (isroom(str[x]))
			cells++;
		return (cells);
}

int		dellist(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		ft_strdel(&str[i]);
		str[i] = NULL;
	}
	free(str);
	return (0);
}

void		getstr(t_date *conf)
{
	char	*str;
	char	*ret;
	int		i;

	i = 0;
	ret = 0;
	while (get_next_line(FD, &str) > 0)
	{
		ft_printf("%s\n", str);
		if (!ret)
			ret = ft_addchr_e(str, '\n');
		else
		{
			ft_strojoin(&ret, str);
			ft_strojoin(&ret, "\n");
		}
	}
	free(str);
	conf->file = ft_strsplit(ret, '\n');
	isvalid(conf) == 0 ? exit(1) : ft_strdel(&ret);
}

int		isroom(char *str)
{
	char	**ret;
	int	 i;

	ret = ft_strsplit(str, ' ');
	i = -1;
	while (ret[++i])
		;
	if ((i != 3 || str[0] == '#') || (!isant(ret[1], 0) || !isant(ret[2], 0)))
		return (dellist(ret));
	dellist(ret);
	return (1);
}

int iscon(char *str)
{
	int	 x;
	char	**ret;

	x = -1;
	ret = ft_strsplit(str, ' ');
	while (ret[++x])
		;
	dellist(ret);
	if (x != 1)
		return (0);
	ret = ft_strsplit(str, '-');
	x = -1;
	while (ret[++x])
		;
	if (x != 2)
		return (dellist(ret));
	dellist(ret);
	return (1);
}

int		isant(char *str, int i)
{
	char	*ant;

	ant = ft_itoa(ft_atoi(str));
	if (!ft_strequ(str, ant) || (i && ft_atoi(str) <= 0))
	{
		ft_strdel(&ant);
		return (0);
	}
	ft_strdel(&ant);
	if (i == 1)
		return (ft_atoi(str));
	return (1);
}

static int  validcomm(char **l, int i, t_date *conf)
{
	static int  st = 0;
	static int  en = 0;
	int         x;

	x = -1;
	while (l[++x])
	if (isant(l[x], 1))
		break ;
	if ((ft_strequ(l[i], "##start") || ft_strequ(l[i], "##end")) && i < x)
		return (0);
	if ((ft_strequ(l[i], "##start") || ft_strequ(l[i], "##end"))
		&& (!l[i + 1] || !isroom(l[i + 1])))
		return (0);
	if (ft_strequ(l[i], "##start") && ((st++) || 1))
		conf->start = x;
	if (ft_strequ(l[i], "##end") && ((en++) || 1))
		conf->end = x;
	if (st > 1 || en > 1)
		return (0);
	return (1);
}

int		isvalid(t_date *conf)
{
	int i;
	int step;

	step = 0;
	i = -1;
	if (!conf->file)
		return (0);
	while (conf->file[++i])
	{
		if (conf->file[i][0] == '#' && conf->file[i][1] != '#')
			continue ;
		if (conf->file[i][0] == '#' && conf->file[i][1] == '#')
		{
			if (!validcomm(conf->file, i, conf))
				return (0);
			continue ;
		}
		if (step == 0 && !((conf->ants = isant(conf->file[i], 1))))
			return (0);
		else if (step == 0 && ((i++) || 1))
			step++;
		if (step == 1 && !isroom(conf->file[i]))
			step++;
		if (step == 2 && (isroom(conf->file[i]) || !iscon(conf->file[i])))
			return (0);
	}
	return (1);
}
