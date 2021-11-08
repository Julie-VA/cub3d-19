#include "cub3d.h"

static char	*get_each_texture(t_map *map, char *prefix, int offset)
{
	int	i;
	int	j;

	i = 0;
	while (map->raw_file[i])
	{
		j = 0;
		while (map->raw_file[i][j] == ' ')
			j++;
		if (!ft_strncmp_space(prefix, map->raw_file[i], offset))
		{
			while (map->raw_file[i][offset + j] == ' ')
				offset++;
			return (map->raw_file[i] + (offset + j));
		}
		i++;
	}
	return (NULL);
}

int	get_textures(t_map *map)
{
	map->n_texture = get_each_texture(map, "NO", 2);
	map->s_texture = get_each_texture(map, "SO", 2);
	map->w_texture = get_each_texture(map, "WE", 2);
	map->e_texture = get_each_texture(map, "EA", 2);
	map->f_color = get_each_texture(map, "F", 1);
	map->c_color = get_each_texture(map, "C", 1);
	if (!map->n_texture || !map->s_texture || !map->w_texture || !map->e_texture || !map->f_color || !map->c_color)
	{
		write(1, "Missing one or more valid texture path(s)\n", 42);
		return (1);
	}
	return (0);
}

static int		check_pos(t_map *map, int x, int y, char ori)
{
	if (map->map_f[y][x] == ori)
	{
		map->p_pos_x = x;
		map->p_pos_y = y;
		map->p_ori = ori;
		return (1);
	}
	return (0);
}

int	get_pos(t_map *map)
{
	int	x;
	int	y;

	y = 1;
	while (map->map_f[y])
	{
		x = 0;
		while (map->map_f[y][x])
		{
			if (check_pos(map, x, y, 'N') || check_pos(map, x, y, 'S')
				|| check_pos(map, x, y, 'W') || check_pos(map, x, y, 'E'))
				return (0);
			x++;
		}
		y++;
	}
	write(1, "No player position or invalid orientation\n", 42);
	return (1);
}
