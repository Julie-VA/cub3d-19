/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:20:18 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/18 18:00:37 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_file(t_file *file)
{
	file->raw_file = NULL;
	file->map = NULL;
}

int	exit_game(t_mlx *mlx_all)
{
	free_all(mlx_all->file);
	free(mlx_all->game);
	free(mlx_all);
	exit(0);
}

int	hook_init(t_vars vars, t_tex tex, t_file *file, t_data buff)
{
	t_mlx			*mlx_all;
	t_game			*game;

	tex.bg_c = get_bg_color("96, 96, 96");
	tex.c_color = file->c_color;
	tex.f_color = file->f_color;
	mlx_all = malloc(sizeof(t_mlx));
	if (!mlx_all)
		return (0);
	game = malloc(sizeof(t_game));
	if (!game)
	{
		free(mlx_all);
		return (0);
	}
	*game = (t_game){player_init(file), file};
	*mlx_all = (t_mlx){vars, tex, buff, game, file};
	mlx_hook(vars.win, 2, 1L << 0, key_press, mlx_all);
	mlx_hook(vars.win, EVENT_DEST, 0, exit_game, mlx_all);
	mlx_loop_hook(vars.mlx, raycast, mlx_all);
	return (1);
}

int	main(int argc, char **argv)
{
	t_file	*file;
	void	*mlx;

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
		return (1);
	mlx = game_init(file);
	if (mlx)
		mlx_loop(mlx);
	return (0);
}
