#include "cub3d.h"

int	parsing(char *argv, t_map *map)
{
	map->raw_file = read_file(argv);
	if (get_textures(map))
		return (1);
	if (get_map(map))
		return (1);
	//check map
	if (get_pos(map))
		return (1);
	return (0);
}
