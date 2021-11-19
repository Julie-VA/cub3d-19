/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:20:18 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/19 12:19:02 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file	*init_t_file(void)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->raw_file = NULL;
	file->map = NULL;
	return (file);
}

int	hook_init(t_vars vars, t_tex tex, t_file *file, t_data buff)
{
	t_mlx		*mlx_all;
	t_player	*p;

	tex.c_color = file->c_color;
	tex.f_color = file->f_color;
	mlx_all = malloc(sizeof(t_mlx));
	if (!mlx_all)
		return (0);
	p = player_init(file);
	if (!p)
	{
		free(mlx_all);
		return (0);
	}
	*mlx_all = (t_mlx){vars, tex, buff, (t_game){p, file->map}, file};
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
			write(2, "Error\nMissing map file\n", 23);
		else if (argc > 2)
			write(2, "Error\nToo many arguments\n", 25);
		return (1);
	}
	if (!check_cub(argv[1]))
		return (1);
	file = init_t_file();
	if (!file || parsing(argv[1], file))
		return (1);
	mlx = game_init(file);
	if (mlx)
		mlx_loop(mlx);
	free_all(file);
	return (1);
}
