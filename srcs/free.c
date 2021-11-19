/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:14:03 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/19 10:54:29 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_file(t_file *file)
{
	int	i;

	i = 0;
	while (file->raw_file[i])
		free(file->raw_file[i++]);
	free(file->raw_file);
	free(file);
	return (1);
}

int	free_all_but_mini(t_file *file)
{
	int	i;

	i = 0;
	while (file->raw_file[i])
		free(file->raw_file[i++]);
	free(file->raw_file);
	i = 0;
	while (file->map[i])
		free(file->map[i++]);
	free(file->map);
	free(file);
	return (1);
}

int	free_all(t_file *file)
{
	int	i;

	i = 0;
	free_all_but_mini(file);
	while (file->minimap[i])
		free(file->minimap[i++]);
	free(file->minimap);
	return (1);
}

int	exit_game(t_mlx *mlx)
{
	free_all(mlx->file);
	free(mlx->game.p);
	mlx_destroy_image(mlx->vars.mlx, mlx->tex.n.img);
	mlx_destroy_image(mlx->vars.mlx, mlx->tex.s.img);
	mlx_destroy_image(mlx->vars.mlx, mlx->tex.w.img);
	mlx_destroy_image(mlx->vars.mlx, mlx->tex.e.img);
	mlx_destroy_image(mlx->vars.mlx, mlx->buff.img);
	mlx_destroy_window(mlx->vars.mlx, mlx->vars.win);
	exit(0);
}
