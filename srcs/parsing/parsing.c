#include "cub3d.h"

int	get_map_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

int	check_around(char **map, int x, int y, int height)
{
	if (y == 0)
	{
		if (map[y + 1][x] == '1' || map[y + 1][x] == ' ')
			if (map[y][x - 1] == '1' || map[y][x - 1] == ' ')
				if (map[y][x + 1] == '1' || map[y][x + 1] == ' ')
					return (0);
	}
	else if (y == height)
	{
		if (map[y - 1][x] == '1' || map[y - 1][x] == ' ')
			if (map[y][x - 1] == '1' || map[y][x - 1] == ' ')
				if (map[y][x + 1] == '1' || map[y][x + 1] == ' ')
					return (0);
	}
	else
	{
		if (map[y - 1][x] == '1' || map[y - 1][x] == ' ')
			if (map[y + 1][x] == '1' || map[y + 1][x] == ' ')
				if (map[y][x - 1] == '1' || map[y][x - 1] == ' ')
					if (map[y][x + 1] == '1' || map[y][x + 1] == ' ')
						return (0);
	}
	return (1);
}

int	check_map(char **map)
{
	int	x;
	int	y;
	int	start;
	int	player;
	int	height;

	y = 0;
	player = 0;
	height = get_map_height(map) - 1;
	while (map[y])
	{
		start = 0;
		x = 0;
		if (y == 0 || y == height)
		{
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
		}
		else
		{
			while (map[y][x] && x < (int)ft_strlen(map[y]))
			{
				while (start == 0 && map[y][x] == ' ')
					x++;
				if (start == 0 && map[y][x] != '1')
					return (1);
				start = 1;
				if (x == (int)ft_strlen(map[y]) - 1 && map[y][x] != '1')
					return (1);
				if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' '
					&& map[y][x] != 'N' && map[y][x] != 'S'
					&& map[y][x] != 'W' && map[y][x] != 'E')
					return (1);
				if (map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'W' || map[y][x] == 'E')
				{
					if (player || y == 0 || y == height || x == 0 || x == (int)ft_strlen(map[y]))
						return (1);
					else
						player = 1;
				}
				if (map[y][x] == ' ')
					if (check_around(map, x, y, height))
						return (1);
				x++;
			}
		}
		y++;
	}
	return (0);
}

int	parsing(char *argv, t_file *file)
{
	file->raw_file = read_file(argv);
	if (!file->raw_file)
		return (1);
	if (get_textures(file))
		return (1);
	if (get_map(file))
		return (1);
	if (check_map(file->map))
	{
		write(1, "wrong file\n", 10);
		return (1);
	}
	if (get_pos(file))
		return (1);
	return (0);
}
