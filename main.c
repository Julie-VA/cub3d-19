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

int     key_press(int keycode, char **map)
{
	if (keycode == KEY_ESC)
			exit(1);
	if (keycode == KEY_W)
	{
		if (map[(int)ppos.y][(int)(ppos.x + pdir.x * 0.2)] != '1')
			ppos.x += pdir.x * 0.2;
		if (map[(int)(ppos.y + pdir.y * 0.2)][(int)ppos.x] != '1')
			ppos.y += pdir.y * 0.2;
	}
	if (keycode == KEY_S)
	{
		if (map[(int)ppos.y][(int)(ppos.x - pdir.x * 0.2)] != '1')
			ppos.x -= pdir.x * 0.2;
		if (map[(int)(ppos.y - pdir.y * 0.2)][(int)ppos.x] != '1')
			ppos.y -= pdir.y * 0.2;
	}
	if (keycode == KEY_D)
	{
		if (map[(int)ppos.y][(int)(ppos.x + pdir.x * cos(1.5708))] != '1')
		{
			ppos.x += pdir.x * cos(1.5708);
			if (map[(int)ppos.y][(int)(ppos.x + (pdir.x * cos(-1.5708) - pdir.y * sin(-1.5708)) * 0.2)] != '1')
				ppos.x += (pdir.x * cos(-1.5708) - pdir.y * sin(-1.5708)) * 0.2;

		}
		if (map[(int)(ppos.y + pdir.y * 0.2)][(int)ppos.x] != '1')
		{
			ppos.y += pdir.y * 0.2;
			if (map[(int)(ppos.y + (pdir.x * sin(-1.5708) + pdir.y * cos(-1.5708)) * 0.2)][(int)ppos.x] != '1')
				ppos.y += (pdir.x * sin(-1.5708) + pdir.y * cos(-1.5708)) * 0.2;
		}
	}
	if (keycode == KEY_A)
	{
		if (map[(int)ppos.y][(int)(ppos.x + pdir.x * cos(1.5708))] != '1')
		{
			ppos.x += pdir.x * cos(1.5708);
			if (map[(int)ppos.y][(int)(ppos.x - (pdir.x * cos(-1.5708) - pdir.y * sin(-1.5708)) * 0.2)] != '1')
				ppos.x -= (pdir.x * cos(-1.5708) - pdir.y * sin(-1.5708)) * 0.2;
		}
		if (map[(int)(ppos.y + pdir.y * 0.2)][(int)ppos.x] != '1')
		{
			ppos.y += pdir.y * 0.2;
			if (map[(int)(ppos.y - (pdir.x * sin(-1.5708) + pdir.y * cos(-1.5708)) * 0.2)][(int)ppos.x] != '1')
				ppos.y -= (pdir.x * sin(-1.5708) + pdir.y * cos(-1.5708)) * 0.2;
		}
	}
	if (keycode == KEY_R)
	{
		double  oldDirx = pdir.x;

		pdir.x = pdir.x * cos(-0.1) - pdir.y * sin(-0.1);
		pdir.y = oldDirx * sin(-0.1) + pdir.y * cos(-0.1);

		double  oldPlaneX = pplane.x;

		pplane.x = pplane.x * cos(-0.1) - pplane.y * sin(-0.1);
		pplane.y = oldPlaneX * sin(-0.1) + pplane.y * cos(-0.1);
	}
	if (keycode == KEY_L)
	{
		double  oldDirx = pdir.x;
		double  oldPlaneX = pplane.x;

		pdir.x = pdir.x * cos(0.1) - pdir.y * sin(0.1);
		pdir.y = oldDirx * sin(0.1) + pdir.y * cos(0.1);

		pplane.x = pplane.x * cos(0.1) - pplane.y * sin(0.1);
		pplane.y = oldPlaneX * sin(0.1) + pplane.y * cos(0.1);
	}
	printf("%d . %d\n", (int)ppos.y, (int)ppos.x);
	return (0);
}

void	hook_init(void *mlx, void *win, t_data *img, t_file *file, t_data *buff, t_data* neuve)
{
	t_mlx	*mlxAll = malloc(sizeof(t_mlx));
	*mlxAll = (t_mlx){win, mlx, img, buff, neuve, file};

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

	if (argc != 2)
	{
		if (argc < 2)
			write(2, "Missing map\n", 11);
		else if (argc > 2)
			write(2, "Too many arguments\n", 19);
		return (1);
	}
	if (!check_cub(argv[1]))
		return (1);
	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (1);
	init_t_file(file);
	if (parsing(argv[1], file))
	{
		system("leaks cub3D");
		return (1);
	}
	mlx = mlx_init();
	ppos = (t_fcoord) {file->p_pos_x, file->p_pos_y};
	pdir = (t_fcoord) {-1, 0};
	pplane = (t_fcoord) {0, 0.66};
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	buff.img = mlx_xpm_file_to_image(mlx, "pics/bg.xpm", &(buff.size.x), &(buff.size.y));
	buff.addr = mlx_get_data_addr(buff.img, &buff.bpp, &buff.line_len, &buff.endian);
	neuve.img = mlx_xpm_file_to_image(mlx, "pics/bg.xpm", &(neuve.size.x), &(neuve.size.y));
	neuve.addr = mlx_get_data_addr(neuve.img, &neuve.bpp, &neuve.line_len, &neuve.endian);
	img.img = mlx_xpm_file_to_image(mlx, "pics/purplestone.xpm", &(img.size.x), &(img.size.y));
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	hook_init(mlx, mlx_win, &img, file, &buff, &neuve);
	mlx_loop(mlx);
	free_all(file);
	return (0);
}
