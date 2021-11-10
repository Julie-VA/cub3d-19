#include "cub3d.h"

void	init_t_map(t_map *map)
{
	map->raw_file = NULL;
	map->map_f = NULL;
}

int	exit_game(void *arg)
{
	(void)arg;
	exit(1);
	return (1);
}

int	key_press(int keycode, void* arg)
{
	(void)arg;
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_W)
	{
		pPos.x += pDir.x * 0.2;
		pPos.y += pDir.y * 0.2;
	}
	if (keycode == KEY_S)
	{
		pPos.x -= pDir.x * 0.2;
		pPos.y -= pDir.y * 0.2;
	}
	if (keycode == KEY_D)
	{
		pPos.x += pDir.x * cos(1.5708) ;
		pPos.y += pDir.y * 0.2;

		pPos.x += (pDir.x * cos(-1.5708) - pDir.y * sin(-1.5708)) * 0.2;
		pPos.y += (pDir.x * sin(-1.5708) + pDir.y * cos(-1.5708)) * 0.2;
		/*
		double	oldDirx = pDir.x;

		pDir.x = pDir.x * cos(-0.1) - pDir.y * sin(-0.1);
		pDir.y = oldDirx * sin(-0.1) + pDir.y * cos(-0.1);

		double	oldPlaneX = plane.x;

		plane.x = plane.x * cos(-0.1) - plane.y * sin(-0.1);
		plane.y = oldPlaneX * sin(-0.1) + plane.y * cos(-0.1);
		*/
	}
	if (keycode == KEY_A)
	{
		double	oldDirx = pDir.x;
		double	oldPlaneX = plane.x;

		pDir.x = pDir.x * cos(0.1) - pDir.y * sin(0.1);
		pDir.y = oldDirx * sin(0.1) + pDir.y * cos(0.1);

		plane.x = plane.x * cos(0.1) - plane.y * sin(0.1);
		plane.y = oldPlaneX * sin(0.1) + plane.y * cos(0.1);
	}
	printf("%d . %d\n", (int)pPos.y, (int)pPos.x);
	return (0);
}

void	hook_init(void *mlx, void *win, t_data *img)
{
	t_mlx	*mlxAll = malloc(sizeof(t_mlx));
	*mlxAll = (t_mlx){win, mlx, img};

	mlx_hook(win, 2, 1L << 0, key_press, NULL);
	mlx_hook(win, EVENT_DEST, 0, exit_game, NULL);
	mlx_loop_hook(mlx, raycast, mlxAll);
}


int	main(int argc, char **argv)
{
	t_map	*map;
	int		i;

	void	*mlx;
	void	*mlx_win;
	t_data	img;

	pPos = (t_fcoord) {4, 4};
	pDir = (t_fcoord) {-1, 0};
	plane = (t_fcoord) {0, 0.66};

	if (argc != 2 || !check_cub(argv[1]))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (1);
	init_t_map(map);
	/*
	if (parsing(argv[1], map))
	{
		system("leaks cub3d");
		return (free_all(map));
	}
	*/
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
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	hook_init(mlx, mlx_win, &img);
	img.img = mlx_xpm_file_to_image(mlx, "pics/coll.xpm", &(img.size.x), &(img.size.y));
	//img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	mlx_loop(mlx);
	free_all(map);
	return (0);
}
