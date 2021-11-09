#include "cub3d.h"

int	get_map_height(char **map_f)
{
	int	y;

	y = 0;
	while (map_f[y])
		y++;
	return (y);
}

int	check_around(char **map_f, int x, int y, int height)
{
	if (y == 0)
	{
		if (map_f[y + 1][x] == '1' || map_f[y + 1][x] == ' ')
			if (map_f[y][x - 1] == '1' || map_f[y][x - 1] == ' ')
				if (map_f[y][x + 1] == '1' || map_f[y][x + 1] == ' ')
					return (0);
	}
	else if (y == height)
	{
		if (map_f[y - 1][x] == '1' || map_f[y - 1][x] == ' ')
			if (map_f[y][x - 1] == '1' || map_f[y][x - 1] == ' ')
				if (map_f[y][x + 1] == '1' || map_f[y][x + 1] == ' ')
					return (0);
	}
	else
	{
		if (map_f[y - 1][x] == '1' || map_f[y - 1][x] == ' ')
			if (map_f[y + 1][x] == '1' || map_f[y + 1][x] == ' ')
				if (map_f[y][x - 1] == '1' || map_f[y][x - 1] == ' ')
					if (map_f[y][x + 1] == '1' || map_f[y][x + 1] == ' ')
						return (0);
	}
	return (1);
}

int	check_map(char **map_f)
{
	int	x;
	int	y;
	int	start;
	int	player;
	int	height;

	y = 0;
	player = 0;
	height = get_map_height(map_f) - 1;
	while (map_f[y])
	{
		start = 0;
		x = 0;
		if (y == 0 || y == height)
		{
			while (map_f[y][x] && x < (int)ft_strlen(map_f[y]))
			{	
				while (start == 0 && map_f[y][x] == ' ')
					x++;
				start = 1;
				if (map_f[y][x] != '1' && map_f[y][x] != ' ')
					return (1);
				if (map_f[y][x] == ' ')
					if (check_around(map_f, x, y, height))
						return (1);
				x++;
			}
		}
		else
		{
			while (map_f[y][x] && x < (int)ft_strlen(map_f[y]))
			{
				while (start == 0 && map_f[y][x] == ' ')
					x++;
				if (start == 0 && map_f[y][x] != '1')
					return (1);
				start = 1;
				if (x == (int)ft_strlen(map_f[y]) - 1 && map_f[y][x] != '1')
					return (1);
				if (map_f[y][x] != '0' && map_f[y][x] != '1' && map_f[y][x] != ' '
					&& map_f[y][x] != 'N' && map_f[y][x] != 'S'
					&& map_f[y][x] != 'W' && map_f[y][x] != 'E')
					return (1);
				if (map_f[y][x] == 'N' || map_f[y][x] == 'S'
					|| map_f[y][x] == 'W' || map_f[y][x] == 'E')
				{
					if (player || y == 0 || y == height || x == 0 || x == (int)ft_strlen(map_f[y]))
						return (1);
					else
						player = 1;
				}
				if (map_f[y][x] == ' ')
					if (check_around(map_f, x, y, height))
						return (1);
				x++;
			}
		}
		y++;
	}
	return (0);
}

int	parsing(char *argv, t_map *map)
{
	map->raw_file = read_file(argv);
	if (get_textures(map))
		return (1);
	if (get_map(map))
		return (1);
	if (check_map(map->map_f))
	{
		write(1, "wrong map\n", 10);
		return (1);
	}
	if (get_pos(map))
		return (1);
	return (0);
}
