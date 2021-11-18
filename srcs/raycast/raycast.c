/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/18 11:19:44 by vneirinc         ###   ########.fr       */
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

	map.x = (int)p->pos.x;
	map.y = (int)p->pos.y;
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
	int			hit;
	t_icoord	step;
	t_icoord	map;
	t_fcoord	side_dist;

	hit = 0;
	map.x = (int)game.p->pos.x;
	map.y = (int)game.p->pos.y;
	side_dist = init_side_dist(ray_dir, game.p, delta_dist, &step);
	while (!hit)
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
		if (game.map[map.y][map.x] == '1')
			hit = 1;
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

int	get_tex_x(int side, t_fcoord ray_dir, float perpWallDist, const t_player *p)
{
	float	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = p->pos.y + perpWallDist * ray_dir.y;
	else
		wall_x = p->pos.x + perpWallDist * ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * 64;
	if (side == 0 && ray_dir.x > 0)
		tex_x = 64 - tex_x - 1;
	if (side == 1 && ray_dir.y < 0)
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

t_data	get_side_tex(int side, t_fcoord ray_dir, t_tex tex)
{
	if (side == 0 && ray_dir.x < 0)
		return (tex.purple);
	else if (side == 0 && ray_dir.x > 0)
		return (tex.blue);
	else if (side == 1 && ray_dir.y > 0)
		return (tex.brick);
	return (tex.grey);
}

void	draw(int lineHeight, t_mlx *mlx, int rays_i,
	t_data tex, int tex_x, t_data img)
{
	int		draw_start;
	int		draw_end;
	float	steptex;
	float	texpos;
	int		i;

	i = 0;
	draw_start = -lineHeight / 2 + SCREEN_H / 2;
	draw_end = lineHeight / 2 + SCREEN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	steptex = 1.0 * 64 / lineHeight;
	texpos = (draw_start - SCREEN_H / 2 + lineHeight / 2) * steptex;
	while (i < draw_start)
		img.addr[i++ * img.size.x + rays_i] = mlx->tex.c_color;
	while (i <= draw_end)
	{
		// normi bug
		img.addr[i * img.size.x + rays_i] = tex.addr[((int)texpos & 63) * tex.size.x + tex_x];
		i++;
		texpos += steptex;
	}
	while (i < SCREEN_H)
		img.addr[i++ * img.size.x + rays_i] = mlx->tex.f_color;
}

int	raycast(t_mlx *mlx)
{
	int			rays_i;
	int			side;
	float		perpWallDist;
	t_fcoord	ray_dir;

	rays_i = 0;
   // struct timeval te; 
    //gettimeofday(&te, NULL); // get current time
    //long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
	while (rays_i < SCREEN_W)
	{
		ray_dir = get_ray_dir(rays_i, mlx->game.p);
		perpWallDist = loop_rays(mlx->game, ray_dir, &side);
		draw(
			SCREEN_H / perpWallDist, mlx, rays_i,
			get_side_tex(side, ray_dir, mlx->tex),
			get_tex_x(side, ray_dir, perpWallDist, mlx->game.p),
			mlx->buff
			);
		rays_i++;
	}
	print_minimap(mlx->minimap, mlx->buff, mlx->tex.bg_c);
	mlx_put_image_to_window(mlx->vars.mlx, mlx->vars.win, mlx->buff.img, 0, 0);
    //gettimeofday(&te, NULL); // get current time
    //long long ms2 = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
	//printf("time: %llu\n", ms2 - milliseconds);
	return 0;
}
