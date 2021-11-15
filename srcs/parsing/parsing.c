/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:48:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/15 15:52:38 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_top_bot(char **map, int x, int y, int height)
{
	int	start;

	start = 0;
	while (map[y][x] && x < (int)ft_strlen(map[y]))
	{	
		while (start == 0 && map[y][x] == ' ')
			x++;
		start = 1;
		if (map[y][x] != '1' && map[y][x] != ' ')
			return (1);
		if (map[y][x] == ' ')
			if (check_around(map, x, y, height))
				return (1);
		x++;
	}
	return (0);
}

static int	check_middle_loop(char **map, int x, int y, int (*vars)[3])
{
	while ((*vars)[1] == 0 && map[y][x] == ' ')
		x++;
	if ((*vars)[1] == 0 && map[y][x] != '1')
		return (-1);
	(*vars)[1] = 1;
	if (x == (int)ft_strlen(map[y]) - 1 && map[y][x] != '1')
		return (-1);
	if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' '
		&& map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'W' && map[y][x] != 'E')
		return (1);
	if (map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		if ((*vars)[2] || y == 0 || y == (*vars)[0] || x == 0
			|| x == (int)ft_strlen(map[y]))
			return (-1);
		else
			(*vars)[2] = 1;
	}
	if (map[y][x] == ' ')
		if (check_around(map, x, y, (*vars)[0]))
			return (-1);
	x++;
	return (x);
}

static int	check_middle(char **map, int x, int y, int height)
{
	int	start;
	int	player;
	int	vars[3];

	start = 0;
	player = 0;
	vars[0] = height;
	vars[1] = start;
	vars[2] = player;
	while (map[y][x] && x < (int)ft_strlen(map[y]))
	{
		x = check_middle_loop(map, x, y, &vars);
		if (x == -1)
			return (1);
	}
	return (0);
}

static int	check_map(char **map)
{
	int	x;
	int	y;
	int	player;
	int	height;

	y = 0;
	player = 0;
	height = get_map_height(map) - 1;
	while (map[y])
	{
		x = 0;
		if (y == 0 || y == height)
		{
			if (check_top_bot(map, x, y, height))
				return (1);
		}
		else
		{
			if (check_middle(map, x, y, height))
				return (1);
		}
		y++;
	}
	return (0);
}

int	parsing(char *argv, t_file *file)
{
	int	i;

	i = 0;
	file->raw_file = read_file(argv);
	if (!file->raw_file)
		return (1);
	if (get_textures(file))
		return (free_file(file));
	if (get_map(file, i))
		return (1);
	if (check_map(file->map))
	{
		write(2, "Invalid map\n", 12);
		return (free_all(file));
	}
	if (get_pos(file))
		return (free_all(file));
	return (0);
}
