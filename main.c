#include "cub3d.h"

void	init_t_map(t_file *file)
{
	file->raw_file = NULL;
	file->map = NULL;
}

int	main(int argc, char **argv)
{
	t_file	*file;
	int		i;

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
	// while (file->raw_file[i])
	// {
	// 	printf("file[%d]=|%s|\n", i, file->raw_file[i]);
	// 	i++;
	// }
	// printf("n_texture=%s\n", file->n_texture);
	// printf("s_texture=%s\n", file->s_texture);
	// printf("w_texture=%s\n", file->w_texture);
	// printf("e_texture=%s\n", file->e_texture);
	// printf("f_color=%s\n", file->f_color);
	// printf("c_color=%s\n", file->c_color);
	// i = 0;
	// while (file->map[i])
	// {
	// 	printf("map[%d]=|%s|\n", i, file->map[i]);
	// 	i++;
	// }
	// printf("p_pos_x=%d\n", file->p_pos_x);
	// printf("p_pos_y=%d\n", file->p_pos_y);
	// printf("p_ori=%c\n", file->p_ori);
	free_all(file);
	system("leaks cub3d");
	return (0);
}
