/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:03:30 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/18 18:02:54 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_w(char **map, t_game *g)
{
	if (map[(int)g->p->pos.y][(int)(g->p->pos.x + g->p->dir.x * 0.2)] != '1')
		g->p->pos.x += g->p->dir.x * 0.2;
	if (map[(int)(g->p->pos.y + g->p->dir.y * 0.2)][(int)g->p->pos.x] != '1')
		g->p->pos.y += g->p->dir.y * 0.2;
}

static void	key_s(char **map, t_game *g)
{
	if (map[(int)g->p->pos.y][(int)(g->p->pos.x - g->p->dir.x * 0.2)] != '1')
		g->p->pos.x -= g->p->dir.x * 0.2;
	if (map[(int)(g->p->pos.y - g->p->dir.y * 0.2)][(int)g->p->pos.x] != '1')
		g->p->pos.y -= g->p->dir.y * 0.2;
}

static void	key_d(char **map, t_game *g)
{
	if (map[(int)g->p->pos.y][(int)(g->p->pos.x + (g->p->dir.x * cos(1.5708)
			- g->p->dir.y * sin(1.5708)) * 0.2)] != '1')
		g->p->pos.x += (g->p->dir.x * cos(1.5708)
				- g->p->dir.y * sin(1.5708)) * 0.2;
	if (map[(int)(g->p->pos.y + (g->p->dir.x * sin(1.5708)
				+ g->p->dir.y * cos(1.5708)) * 0.2)][(int)g->p->pos.x] != '1')
		g->p->pos.y += (g->p->dir.x * sin(1.5708)
				+ g->p->dir.y * cos(1.5708)) * 0.2;
}

static void	key_a(char **map, t_game *g)
{
	if (map[(int)g->p->pos.y][(int)(g->p->pos.x + (g->p->dir.x * cos(-1.5708)
			- g->p->dir.y * sin(-1.5708)) * 0.2)] != '1')
		g->p->pos.x += (g->p->dir.x * cos(-1.5708)
				- g->p->dir.y * sin(-1.5708)) * 0.2;
	if (map[(int)(g->p->pos.y + (g->p->dir.x * sin(-1.5708)
				+ g->p->dir.y * cos(-1.5708)) * 0.2)][(int)g->p->pos.x] != '1')
		g->p->pos.y += (g->p->dir.x * sin(-1.5708)
				+ g->p->dir.y * cos(-1.5708)) * 0.2;
}

int	key_press(int keycode, t_mlx *mlx_all)
{
	char	**map;
	float	old_dirx;
	float	old_planex;

	map = mlx_all->game->file->map;
	old_dirx = mlx_all->game->p->dir.x;
	old_planex = mlx_all->game->p->plane.x;
	if (keycode == KEY_ESC)
	{
		free_all(mlx_all->game->file);
		exit(0);
	}
	if (keycode == KEY_W)
		key_w(map, mlx_all->game);
	if (keycode == KEY_S)
		key_s(map, mlx_all->game);
	if (keycode == KEY_D)
		key_d(map, mlx_all->game);
	if (keycode == KEY_A)
		key_a(map, mlx_all->game);
	if (keycode == KEY_R)
		key_r(mlx_all->game, old_dirx, old_planex);
	if (keycode == KEY_L)
		key_l(mlx_all->game, old_dirx, old_planex);
	return (0);
}
