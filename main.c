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
	system("leaks cub3D");
	return (1);
}

/*
int     key_press(int keycode, char **map)
{
	if (keycode == KEY_ESC)
	{
		system("leaks cub3D");
		exit(1);
	}
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
		float  oldDirx = pdir.x;

		pdir.x = pdir.x * cos(-0.1) - pdir.y * sin(-0.1);
		pdir.y = oldDirx * sin(-0.1) + pdir.y * cos(-0.1);

		float  oldPlaneX = pplane.x;

		pplane.x = pplane.x * cos(-0.1) - pplane.y * sin(-0.1);
		pplane.y = oldPlaneX * sin(-0.1) + pplane.y * cos(-0.1);
	}
	if (keycode == KEY_L)
	{
		float  oldDirx = pdir.x;
		float  oldPlaneX = pplane.x;

		pdir.x = pdir.x * cos(0.1) - pdir.y * sin(0.1);
		pdir.y = oldDirx * sin(0.1) + pdir.y * cos(0.1);

		pplane.x = pplane.x * cos(0.1) - pplane.y * sin(0.1);
		pplane.y = oldPlaneX * sin(0.1) + pplane.y * cos(0.1);
	}
	return (0);
}
*/

int	hook_init(t_vars vars, t_tex tex, t_file *file, t_data buff)
{
	t_mlx			*mlxAll;
	t_game			*game;
	
	tex.bg_c = get_bg_color("96, 96, 96");
	tex.c_color = file->c_color;
	tex.f_color = file->f_color;
	mlxAll = malloc(sizeof(t_mlx));
	game = malloc(sizeof(t_game));
	*game = (t_game){game_init(file), file->map};
	*mlxAll = (t_mlx){vars, tex, buff, *game, file->minimap};
	mlx_hook(vars.win, 2, 1L << 0, key_pressnew, game);
	mlx_hook(vars.win, EVENT_DEST, 0, exit_game, NULL);
	mlx_loop_hook(vars.mlx, raycast, mlxAll);
	return (1);
}

int	main(int argc, char **argv)
{
	t_file	*file;
	t_vars	vars;
	t_tex	tex;
	t_data	buff;

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
	vars.mlx = mlx_init();
	buff.img = mlx_new_image(vars.mlx, SCREEN_W, SCREEN_H);
	buff.addr = mlx_get_data_addr(buff.img, &buff.bpp, &buff.line_len, &buff.endian);
	tex.purple.img = mlx_xpm_file_to_image(vars.mlx, "pics/purplestone.xpm", &(tex.purple.size.x), &(tex.purple.size.y));
	tex.purple.addr = mlx_get_data_addr(tex.purple.img, &tex.purple.bpp, &tex.purple.line_len, &tex.purple.endian);
	tex.blue.img = mlx_xpm_file_to_image(vars.mlx, "pics/bluestone.xpm", &(tex.blue.size.x), &(tex.blue.size.y));
	tex.blue.addr = mlx_get_data_addr(tex.blue.img, &tex.blue.bpp, &tex.blue.line_len, &tex.blue.endian);
	tex.grey.img = mlx_xpm_file_to_image(vars.mlx, "pics/greystone.xpm", &(tex.grey.size.x), &(tex.grey.size.y));
	tex.grey.addr = mlx_get_data_addr(tex.grey.img, &tex.grey.bpp, &tex.grey.line_len, &tex.grey.endian);
	tex.brick.img = mlx_xpm_file_to_image(vars.mlx, "pics/redbrick.xpm", &(tex.brick.size.x), &(tex.brick.size.y));
	tex.brick.addr = mlx_get_data_addr(tex.brick.img, &tex.brick.bpp, &tex.brick.line_len, &tex.brick.endian);
	vars.win = mlx_new_window(vars.mlx, SCREEN_W, SCREEN_H, "cub3D");
	hook_init(vars, tex, file, buff);
	mlx_loop(vars.mlx);
	return (0);
}
