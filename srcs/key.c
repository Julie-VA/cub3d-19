/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:03:30 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/18 16:08:09 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressnew(int keycode, t_game *game)
{
	char**	map;

	map = game->map;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
	{
		if (map[(int)game->p->pos.y][(int)(game->p->pos.x + game->p->dir.x * 0.2)] != '1')
			game->p->pos.x += game->p->dir.x * 0.2;
		if (map[(int)(game->p->pos.y + game->p->dir.y * 0.2)][(int)game->p->pos.x] != '1')
			game->p->pos.y += game->p->dir.y * 0.2;
	}
	if (keycode == KEY_S)
	{
		if (map[(int)game->p->pos.y][(int)(game->p->pos.x - game->p->dir.x * 0.2)] != '1')
			game->p->pos.x -= game->p->dir.x * 0.2;
		if (map[(int)(game->p->pos.y - game->p->dir.y * 0.2)][(int)game->p->pos.x] != '1')
			game->p->pos.y -= game->p->dir.y * 0.2;
	}
	if (keycode == KEY_D)
	{
		if (map[(int)game->p->pos.y][(int)(game->p->pos.x + (game->p->dir.x * cos(1.5708) - game->p->dir.y * sin(1.5708)) * 0.2)] != '1')
			game->p->pos.x += (game->p->dir.x * cos(1.5708) - game->p->dir.y * sin(1.5708)) * 0.2;
		if (map[(int)(game->p->pos.y + (game->p->dir.x * sin(1.5708) + game->p->dir.y * cos(1.5708)) * 0.2)][(int)game->p->pos.x] != '1')
			game->p->pos.y += (game->p->dir.x * sin(1.5708) + game->p->dir.y * cos(1.5708)) * 0.2;
	}
	if (keycode == KEY_A)
	{
		if (map[(int)game->p->pos.y][(int)(game->p->pos.x + (game->p->dir.x * cos(-1.5708) - game->p->dir.y * sin(-1.5708)) * 0.2)] != '1')
			game->p->pos.x += (game->p->dir.x * cos(-1.5708) - game->p->dir.y * sin(-1.5708)) * 0.2;
		if (map[(int)(game->p->pos.y + (game->p->dir.x * sin(-1.5708) + game->p->dir.y * cos(-1.5708)) * 0.2)][(int)game->p->pos.x] != '1')
			game->p->pos.y += (game->p->dir.x * sin(-1.5708) + game->p->dir.y * cos(-1.5708)) * 0.2;
	}
	if (keycode == KEY_R)
	{
		float	oldDirx = game->p->dir.x;
		float	oldPlaneX = game->p->plane.x;

		game->p->dir.x = game->p->dir.x * cos(0.1) - game->p->dir.y * sin(0.1);
		game->p->dir.y = oldDirx * sin(0.1) + game->p->dir.y * cos(0.1);

		game->p->plane.x = game->p->plane.x * cos(0.1) - game->p->plane.y * sin(0.1);
		game->p->plane.y = oldPlaneX * sin(0.1) + game->p->plane.y * cos(0.1);
	}
	if (keycode == KEY_L)
	{
		float	oldDirx = game->p->dir.x;
		float	oldPlaneX = game->p->plane.x;

		game->p->dir.x = game->p->dir.x * cos(-0.1) - game->p->dir.y * sin(-0.1);
		game->p->dir.y = oldDirx * sin(-0.1) + game->p->dir.y * cos(-0.1);

		game->p->plane.x = game->p->plane.x * cos(-0.1) - game->p->plane.y * sin(-0.1);
		game->p->plane.y = oldPlaneX * sin(-0.1) + game->p->plane.y * cos(-0.1);
	}
	return (0);
}