#include "cub3d.h"

char	*get_each_texture(t_map *map, char *prefix, int offset)
{
	int	i;

	i = 0;
	while (map->raw_file[i])
	{
		if (!ft_strncmp(prefix, map->raw_file[i], offset))
		{
			while (map->raw_file[i][offset] == ' ')
				offset++;
			return (map->raw_file[i] + offset);
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
		write(1, "Wrong texture path\n", 19);
		return (1);
	}
	return (0);
}

int	parse_map(char *argv, t_map *map)
{
	map->raw_file = read_file(argv);
	if (get_textures(map))
		return (1);
	return (0);
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
	if (parse_map(argv[1], map))
		return (1); //error
	i = 0;
	while (map->raw_file[i])
	{
		printf("map[%d]=%s\n", i, map->raw_file[i]);
		i++;
	}
	printf("n_texture=%s\n", map->n_texture);
	printf("s_texture=%s\n", map->s_texture);
	printf("w_texture=%s\n", map->w_texture);
	printf("e_texture=%s\n", map->e_texture);
	printf("f_color=%s\n", map->f_color);
	printf("c_color=%s\n", map->c_color);

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_W, SCREEN_H, "RAYCAST!");
	img.img = mlx_new_image(mlx, SCREEN_W, SCREEN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	raycast(map->map_f, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
