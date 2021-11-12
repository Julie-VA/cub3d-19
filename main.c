#include "cub3d.h"

void	init_t_file(t_file *file)
{
	file->raw_file = NULL;
	file->map = NULL;
}

int	exit_game(void *arg)
{
	(void)arg;
	exit(1);
	return (1);
}

void	hook_init(void *mlx, void *win, t_data *img, t_file *file, t_player player, t_data *buff, t_data* neuve)
{
	t_mlx	*mlxAll = malloc(sizeof(t_mlx));
	*mlxAll = (t_mlx){win, mlx, img, buff, neuve, file, player};

	mlx_hook(win, 2, 1L << 0, key_press, file->map);
	mlx_hook(win, EVENT_DEST, 0, exit_game, NULL);
	mlx_loop_hook(mlx, raycast, mlxAll);
}


int	main(int argc, char **argv)
{
	t_file	*file;
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_data	buff;
	t_data	neuve;

	t_player	player;

	if (argc != 2 || !check_cub(argv[1]))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (1);
	init_t_file(file);
	if (parsing(argv[1], file))
	{
		system("leaks cub3d");
		return (free_all(file));
	}
	mlx = mlx_init();
	player.pos = (t_fcoord) {file->p_pos_x, file->p_pos_y};
	player.dir = (t_fcoord) {-1, 0};
	player.plane = (t_fcoord) {0, 0.66};
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	buff.img = mlx_xpm_file_to_image(mlx, "pics/bg.xpm", &(buff.size.x), &(buff.size.y));
	buff.addr = mlx_get_data_addr(buff.img, &buff.bpp, &buff.line_len, &buff.endian);
	neuve.img = mlx_xpm_file_to_image(mlx, "pics/bg.xpm", &(neuve.size.x), &(neuve.size.y));
	neuve.addr = mlx_get_data_addr(neuve.img, &neuve.bpp, &neuve.line_len, &neuve.endian);
	img.img = mlx_xpm_file_to_image(mlx, "pics/purplestone.xpm", &(img.size.x), &(img.size.y));
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	hook_init(mlx, mlx_win, &img, file, player, &buff, &neuve);
	mlx_loop(mlx);
	free_all(file);
	return (0);
}
