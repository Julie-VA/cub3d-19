#include "cub3d.h"

int	free_all(t_file *file)
{
	int	i;

	i = 0;
	while (file->raw_file[i])
		free(file->raw_file[i++]);
	free(file->raw_file);
	i = 0;
	while (file->map[i])
		free(file->map[i++]);
	free(file->map);
	free(file);
	return (1);
}