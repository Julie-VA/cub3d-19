#include "cub3d.h"

int	free_all(t_map *map)
{
	int	i;

	i = 0;
	while (map->raw_file[i])
		free(map->raw_file[i++]);
	free(map->raw_file);
	i = 0;
	while (map->map_f[i])
		free(map->map_f[i++]);
	free(map->map_f);
	free(map);
	return (1);
}