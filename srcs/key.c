/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:03:30 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/19 10:35:00 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_w(char **map, t_player *p)
{
	if (map[(int)p->pos.y][(int)(p->pos.x + p->dir.x * 0.2)] != '1')
		p->pos.x += p->dir.x * 0.2;
	if (map[(int)(p->pos.y + p->dir.y * 0.2)][(int)p->pos.x] != '1')
		p->pos.y += p->dir.y * 0.2;
}

static void	key_s(char **map, t_player *p)
{
	if (map[(int)p->pos.y][(int)(p->pos.x - p->dir.x * 0.2)] != '1')
		p->pos.x -= p->dir.x * 0.2;
	if (map[(int)(p->pos.y - p->dir.y * 0.2)][(int)p->pos.x] != '1')
		p->pos.y -= p->dir.y * 0.2;
}

static void	key_d(char **map, t_player *p)
{
	if (map[(int)p->pos.y][(int)(p->pos.x + (p->dir.x * cos(1.5708)
			- p->dir.y * sin(1.5708)) * 0.2)] != '1')
		p->pos.x += (p->dir.x * cos(1.5708)
				- p->dir.y * sin(1.5708)) * 0.2;
	if (map[(int)(p->pos.y + (p->dir.x * sin(1.5708)
				+ p->dir.y * cos(1.5708)) * 0.2)][(int)p->pos.x] != '1')
		p->pos.y += (p->dir.x * sin(1.5708)
				+ p->dir.y * cos(1.5708)) * 0.2;
}

static void	key_a(char **map, t_player *p)
{
	if (map[(int)p->pos.y][(int)(p->pos.x + (p->dir.x * cos(-1.5708)
			- p->dir.y * sin(-1.5708)) * 0.2)] != '1')
		p->pos.x += (p->dir.x * cos(-1.5708)
				- p->dir.y * sin(-1.5708)) * 0.2;
	if (map[(int)(p->pos.y + (p->dir.x * sin(-1.5708)
				+ p->dir.y * cos(-1.5708)) * 0.2)][(int)p->pos.x] != '1')
		p->pos.y += (p->dir.x * sin(-1.5708)
				+ p->dir.y * cos(-1.5708)) * 0.2;
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
		key_w(mlx->map, mlx->p);
	if (keycode == KEY_S)
		key_s(mlx->map, mlx->p);
	if (keycode == KEY_D)
		key_d(mlx->map, mlx->p);
	if (keycode == KEY_A)
		key_a(mlx->map, mlx->p);
	if (keycode == KEY_R)
		key_r(mlx->p, mlx->p->dir.x, mlx->p->plane.x);
	if (keycode == KEY_L)
		key_l(mlx->p, mlx->p->dir.x, mlx->p->plane.x);
	return (0);
}
