/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:03:30 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/12 12:13:58 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game* game)
{
	char**	map = game->map;
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_W)
	{
		if (map[(int)game->player.pos.y][(int)(game->player.pos.x + game->player.dir.x * 0.2)] != '1')
			game->player.pos.x += game->player.dir.x * 0.2;
		if (map[(int)(game->player.pos.y + game->player.dir.y * 0.2)][(int)game->player.pos.x] != '1')
			game->player.pos.y += game->player.dir.y * 0.2;
	}
	if (keycode == KEY_S)
	{
		if (map[(int)game->player.pos.y][(int)(game->player.pos.x - game->player.dir.x * 0.2)] != '1')
			game->player.pos.x -= game->player.dir.x * 0.2;
		if (map[(int)(game->player.pos.y - game->player.dir.y * 0.2)][(int)game->player.pos.x] != '1')
			game->player.pos.y -= game->player.dir.y * 0.2;
	}
	if (keycode == KEY_A)
	{
		game->player.pos.x += (game->player.dir.x * cos(1.5708) - game->player.dir.y * sin(1.5708)) * 0.2;
		game->player.pos.y += (game->player.dir.x * sin(1.5708) + game->player.dir.y * cos(1.5708)) * 0.2;
	}
	if (keycode == KEY_D)
	{
		game->player.pos.x += (game->player.dir.x * cos(-1.5708) - game->player.dir.y * sin(-1.5708)) * 0.2;
		game->player.pos.y += (game->player.dir.x * sin(-1.5708) + game->player.dir.y * cos(-1.5708)) * 0.2;
	}
	if (keycode == KEY_L)
	{
		double	oldDirx = game->player.dir.x;
		double	oldPlaneX = game->player.plane.x;

		game->player.dir.x = game->player.dir.x * cos(0.1) - game->player.dir.y * sin(0.1);
		game->player.dir.y = oldDirx * sin(0.1) + game->player.dir.y * cos(0.1);

		game->player.plane.x = game->player.plane.x * cos(0.1) - game->player.plane.y * sin(0.1);
		game->player.plane.y = oldPlaneX * sin(0.1) + game->player.plane.y * cos(0.1);
	}
	if (keycode == KEY_R)
	{
		double	oldDirx = game->player.dir.x;
		double	oldPlaneX = game->player.plane.x;

		game->player.dir.x = game->player.dir.x * cos(-0.1) - game->player.dir.y * sin(-0.1);
		game->player.dir.y = oldDirx * sin(-0.1) + game->player.dir.y * cos(-0.1);

		game->player.plane.x = game->player.plane.x * cos(-0.1) - game->player.plane.y * sin(-0.1);
		game->player.plane.y = oldPlaneX * sin(-0.1) + game->player.plane.y * cos(-0.1);
	}
	return (0);
}