/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:48:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/19 12:16:41 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_top_bot(char **map, int x, int y, int height)
{
	int	start;

	start = 0;
	while (map[y][x] && x < (int)ft_strlen(map[y]))
	{
		while (start == 0 && is_space(map[y][x]))
			x++;
		start = 1;
		if (map[y][x] != '1' && !is_space(map[y][x]))
			return (1);
		if (is_space(map[y][x]))
			if (check_around(map, x, y, height))
				return (1);
		x++;
	}
	return (0);
}

static int	check_middle_loop(char **m, t_icoord xy, int vars[2], int *player)
{
	while (!vars[1] && is_space(m[xy.y][xy.x]))
		xy.x++;
	if (vars[1] == 0 && m[xy.y][xy.x] != '1')
		return (-1);
	vars[1] = 1;
	if (xy.x == (int)ft_strlen(m[xy.y]) - 1 && m[xy.y][xy.x] != '1')
		return (-1);
	if (m[xy.y][xy.x] != '0' && m[xy.y][xy.x] != '1' && !is_space(m[xy.y][xy.x])
		&& m[xy.y][xy.x] != 'N' && m[xy.y][xy.x] != 'S' && m[xy.y][xy.x] != 'W'
		&& m[xy.y][xy.x] != 'E')
		return (1);
	if (m[xy.y][xy.x] == 'N' || m[xy.y][xy.x] == 'S'
		|| m[xy.y][xy.x] == 'W' || m[xy.y][xy.x] == 'E')
	{
		if (*player == 1 || xy.y == 0 || xy.y == vars[0] || xy.x == 0
			|| xy.x == (int)ft_strlen(m[xy.y]))
			return (-1);
		else
			*player = 1;
	}
	if (m[xy.y][xy.x] == ' ')
		if (check_around(m, xy.x, xy.y, vars[0]))
			return (-1);
	xy.x++;
	return (xy.x);
}

static int	check_middle(char **map, t_icoord xy, int height, int *player)
{
	int	vars[2];

	vars[0] = height;
	vars[1] = 0;
	while (map[xy.y][xy.x] && xy.x < (int)ft_strlen(map[xy.y]))
	{
		xy.x = check_middle_loop(map, xy, vars, player);
		if (xy.x == -1)
			return (1);
	}
	return (0);
}

static int	check_map(char **map)
{
	t_icoord	xy;
	int			player;
	int			height;

	xy.y = 0;
	player = 0;
	height = get_map_height(map) - 1;
	while (map[xy.y])
	{
		xy.x = 0;
		if (xy.y == 0 || xy.y == height)
		{
			if (check_top_bot(map, xy.x, xy.y, height))
				return (1);
		}
		else
		{
			if (check_middle(map, xy, height, &player))
				return (1);
		}
		xy.y++;
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
		return (free_all_but_mini(file, 0));
	if (get_map(file, i))
		return (1);
	if (check_map(file->map))
	{
		write(2, "Error\nInvalid map\n", 18);
		return (free_all_but_mini(file, 1));
	}
	if (get_pos(file))
		return (free_all_but_mini(file, 1));
	file->minimap = set_minimap(file);
	if (!file->minimap)
		return (free_all_but_mini(file, 1));
	return (0);
}
