/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/18 14:36:42 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_fcoord	get_ray_dir(int rays_i, t_player *p)
{
	t_fcoord	ray_dir;
	float		camera_x;

	camera_x = 2 * rays_i / ((float)SCREEN_W) - 1;
	ray_dir.x = p->dir.x + p->plane.x * camera_x;
	ray_dir.y = p->dir.y + p->plane.y * camera_x;
	return (ray_dir);
}

t_fcoord	init_side_dist(t_fcoord ray_dir, t_player *p,
	t_fcoord delta_dist, t_icoord *step)
{
	t_fcoord	side_dist;
	t_icoord	map;

	map = (t_icoord){p->pos.x, p->pos.y};
	if (ray_dir.x < 0)
	{
		step->x = -1;
		side_dist.x = (p->pos.x - map.x) * delta_dist.x;
	}
	else
	{
		step->x = 1;
		side_dist.x = (map.x + 1.0 - p->pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step->y = -1;
		side_dist.y = (p->pos.y - map.y) * delta_dist.y;
	}
	else
	{
		step->y = 1;
		side_dist.y = (map.y + 1.0 - p->pos.y) * delta_dist.y;
	}
	return (side_dist);
}

float	launch_rays(const t_game game, t_fcoord delta_dist,
	t_fcoord ray_dir, int *side)
{
	t_icoord	step;
	t_icoord	map;
	t_fcoord	side_dist;

	map = (t_icoord){game.p->pos.x, game.p->pos.y};
	side_dist = init_side_dist(ray_dir, game.p, delta_dist, &step);
	while (game.map[map.y][map.x] != '1')
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map.x += step.x;
			*side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			*side = 1;
		}
	}
	if (*side == 0)
		return (side_dist.x - delta_dist.x);
	return (side_dist.y - delta_dist.y);
}

float	loop_rays(t_game game, t_fcoord ray_dir, int *side)
{
	t_fcoord	delta_dist;

	if (ray_dir.x != 0)
		delta_dist.x = fabs(1 / ray_dir.x);
	else
		delta_dist.x = MAXFLOAT;
	if (ray_dir.y != 0)
		delta_dist.y = fabs(1 / ray_dir.y);
	else
		delta_dist.y = MAXFLOAT;
	return (launch_rays(game, delta_dist, ray_dir, side));
}

int	raycast(t_mlx *mlx)
{
	int			rays_i;
	int			side;
	float		perp_wall_dist;
	t_fcoord	ray_dir;

	rays_i = 0;
	while (rays_i < SCREEN_W)
	{
		ray_dir = get_ray_dir(rays_i, mlx->game.p);
		perp_wall_dist = loop_rays(mlx->game, ray_dir, &side);
		draw(
			SCREEN_H / perp_wall_dist, mlx->tex,
			mlx->buff.addr + rays_i,
			get_side_tex(side, ray_dir, mlx->tex).addr
			+ get_tex_x(side, ray_dir, perp_wall_dist, mlx->game.p)
			);
		rays_i++;
	}
	print_minimap(mlx->minimap, mlx->buff, mlx->tex.bg_c);
	draw_player(mlx->multipl, mlx->buff, mlx->game.p);
	mlx_put_image_to_window(mlx->vars.mlx, mlx->vars.win, mlx->buff.img, 0, 0);
	return (0);
}
