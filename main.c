#include "cub3d.h"

void	init_t_map(t_map *map)
{
	map->raw_file = NULL;
	map->map_f = NULL;
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		i;

	void	*mlx;
	void	*mlx_win;
	t_data	img;

	

	if (argc != 2 || !check_cub(argv[1]))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (1);
	init_t_map(map);
	if (parsing(argv[1], map))
	{
		system("leaks cub3d");
		return (free_all(map));
	}
	i = 0;
	// while (map->raw_file[i])
	// {
	// 	printf("map[%d]=%s\n", i, map->raw_file[i]);
	// 	i++;
	// }
	// printf("n_texture=%s\n", map->n_texture);
	// printf("s_texture=%s\n", map->s_texture);
	// printf("w_texture=%s\n", map->w_texture);
	// printf("e_texture=%s\n", map->e_texture);
	// printf("f_color=%s\n", map->f_color);
	// printf("c_color=%s\n", map->c_color);
	// i = 0;
	// while (map->map_f[i])
	// {
	// 	printf("map_f[%d]=%s\n", i, map->map_f[i]);
	// 	i++;
	// }
	// printf("p_pos_x=%d\n", map->p_pos_x);
	// printf("p_pos_y=%d\n", map->p_pos_y);
	// printf("p_ori=%c\n", map->p_ori);
	free_all(map);
	system("leaks cub3d");
	return (0);
}
