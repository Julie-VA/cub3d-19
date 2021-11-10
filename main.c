#include "cub3d.h"

void	init_t_map(t_file *file)
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
	}
	if (keycode == KEY_A)
	{
		pPos.x += pDir.x * cos(1.5708) ;
		pPos.y += pDir.y * 0.2;

		pPos.x -= (pDir.x * cos(-1.5708) - pDir.y * sin(-1.5708)) * 0.2;
		pPos.y -= (pDir.x * sin(-1.5708) + pDir.y * cos(-1.5708)) * 0.2;
	}
	if (keycode == KEY_R)
	{
		double	oldDirx = pDir.x;

		pDir.x = pDir.x * cos(-0.1) - pDir.y * sin(-0.1);
		pDir.y = oldDirx * sin(-0.1) + pDir.y * cos(-0.1);

		double	oldPlaneX = plane.x;

		plane.x = plane.x * cos(-0.1) - plane.y * sin(-0.1);
		plane.y = oldPlaneX * sin(-0.1) + plane.y * cos(-0.1);
	}
	if (keycode == KEY_L)
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

void	hook_init(void *mlx, void *win, t_data *img, t_data *black)
{
	t_mlx	*mlxAll = malloc(sizeof(t_mlx));
	*mlxAll = (t_mlx){win, mlx, img, black};

	mlx_hook(win, 2, 1L << 0, key_press, NULL);
	mlx_hook(win, EVENT_DEST, 0, exit_game, NULL);
	mlx_loop_hook(mlx, raycast, mlxAll);
}


int	main(int argc, char **argv)
{
	t_file	*file;

	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_data	black;

	

	pPos = (t_fcoord) {4, 4};
	pDir = (t_fcoord) {-1, 0};
	plane = (t_fcoord) {0, 0.66};

	if (argc != 2 || !check_cub(argv[1]))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (1);
	init_t_map(file);
	/*
	if (parsing(argv[1], map))
	{
		system("leaks cub3d");
		return (free_all(file));
	}
	*/
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	black.img = mlx_new_image(mlx, 1920, 1080);
	black.addr = mlx_get_data_addr(black.img, &black.bpp, &black.line_len, &black.endian);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	for (int x = 0; x < SCREEN_W; x++)
		for (int y = 0; y < SCREEN_H; y++)
			set_px(&black, (t_icoord){x, y}, 0);

	hook_init(mlx, mlx_win, &img, &black);
	mlx_loop(mlx);
	free_all(file);
	return (0);
}
