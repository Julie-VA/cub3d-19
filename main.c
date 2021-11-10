#include "cub3d.h"

void	init_t_map(t_file *file)
{
	file->raw_file = NULL;
	file->map = NULL;
}

int	main(int argc, char **argv)
{
	t_file	*file;

	if (argc != 2 || !check_cub(argv[1]))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (1);
	init_t_map(file);
	if (parsing(argv[1], file))
	{
		system("leaks cub3d");
		return (free_all(file));
	}
	i = 0;
	free_all(file);
	system("leaks cub3d");
	return (0);
}
