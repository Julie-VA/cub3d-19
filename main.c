/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:20:18 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/18 16:01:50 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_file(t_file *file)
{
	file->raw_file = NULL;
	file->map = NULL;
}

int	exit_game(void *arg)
{
	(void)arg;
	exit(0);
	system("leaks cub3D");
	return (1);
}

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
	*mlxAll = (t_mlx){vars, tex, buff, *game, file->minimap, file->multipl};
	mlx_hook(vars.win, 2, 1L << 0, key_press, game);
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
	buff.size = (t_icoord) {SCREEN_W, SCREEN_H};
	buff.addr = (unsigned int *)mlx_get_data_addr(buff.img, &buff.bpp, &buff.line_len, &buff.endian);
	if (!tex_init(file, vars.mlx, &tex))
		return (1);
	vars.win = mlx_new_window(vars.mlx, SCREEN_W, SCREEN_H, "cub3D");
	hook_init(vars, tex, file, buff);
	mlx_loop(vars.mlx);
	return (0);
}
