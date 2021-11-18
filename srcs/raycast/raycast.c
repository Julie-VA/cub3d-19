/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/18 10:54:40 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_fcoord	get_ray_dir(int rays_i, t_player *p)
{
	t_fcoord	rayDir;
	float		cameraX = 2 * rays_i / ((float)SCREEN_W) - 1;;

	rayDir.x = p->dir.x + p->plane.x * cameraX;
	rayDir.y = p->dir.y + p->plane.y * cameraX;
	return (rayDir);
}

t_fcoord	init_side_dist(t_fcoord rayDir, t_player *p, t_fcoord deltaDist, t_icoord *step)
{
	t_fcoord	sideDist;
	t_icoord	map;

	map.x = (int)p->pos.x; 
	map.y = (int)p->pos.y; 
	if (rayDir.x < 0)
	{
		step->x = -1;
		sideDist.x = (p->pos.x - map.x) * deltaDist.x;
	}
	else
	{
		step->x = 1;
		sideDist.x = (map.x + 1.0 - p->pos.x) * deltaDist.x;
	}
	if (rayDir.y < 0)
	{
		step->y = -1;
		sideDist.y = (p->pos.y - map.y) * deltaDist.y;
	}
	else
	{
		step->y = 1;
		sideDist.y = (map.y + 1.0 - p->pos.y) * deltaDist.y;
	}
	return (sideDist);
}
float	launch_rays(const t_game game, t_fcoord deltaDist, t_fcoord rayDir, int *side)
{
	int	hit = 0;
	t_icoord	step;
	t_icoord	map;
	t_fcoord	sideDist;

	map.x = (int)game.p->pos.x; 
	map.y = (int)game.p->pos.y; 
	sideDist = init_side_dist(rayDir, game.p, deltaDist, &step);
	while(!hit)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			map.x += step.x;
			*side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			map.y += step.y;
			*side = 1;
		}
		if (game.map[map.y][map.x] == '1')
			hit = 1;
	}
	if (*side == 0)
		return sideDist.x - deltaDist.x;
	return sideDist.y - deltaDist.y;
}

float	loop_rays(t_game game, t_fcoord rayDir, int *side)
{
	t_fcoord	deltaDist;
	float	dist;

	if (rayDir.x != 0)
		deltaDist.x = fabs(1 / rayDir.x);
	else
		deltaDist.x = MAXFLOAT;
	if (rayDir.y != 0)
		deltaDist.y = fabs(1 / rayDir.y);
	else
		deltaDist.y = MAXFLOAT;
	dist = launch_rays(game, deltaDist, rayDir, side);
	return dist;
}

int	get_tex_x(int side, t_fcoord rayDir, float perpWallDist, const t_player *p)
{
	float	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = p->pos.y + perpWallDist * rayDir.y;
	else
		wall_x = p->pos.x + perpWallDist * rayDir.x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * 64;
	if(side == 0 && rayDir.x > 0)
		tex_x = 64 - tex_x - 1;
	if(side == 1 && rayDir.y < 0)
		tex_x = 64 - tex_x - 1;
	return (tex_x);
}

t_data	get_side_tex(int side, t_fcoord rayDir, t_tex tex)
{
	if (side == 0 && rayDir.x < 0)
		return (tex.purple);
	else if (side == 0 && rayDir.x > 0)
		return (tex.blue);
	else if (side == 1 && rayDir.y > 0)
		return (tex.brick);
	return (tex.grey);
}

void  draw(int lineHeight, t_mlx *mlx, int rays_i, t_data tex, int tex_x, t_data img)
{
	int	drawStart;
	int	drawEnd;
	float steptex;
	float texPos;

    drawStart = -lineHeight / 2 + SCREEN_H / 2;
    drawEnd = lineHeight / 2 + SCREEN_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= SCREEN_H)
		drawEnd = SCREEN_H - 1;
	steptex = 1.0 * 64 / lineHeight;
	texPos = (drawStart - SCREEN_H / 2 + lineHeight / 2) * steptex;
	for (int i = 0; i < drawStart; i++)
		img.addr[i * img.size.x + rays_i] = mlx->tex.c_color;
	while (drawStart <= drawEnd)
	{
		img.addr[drawStart * img.size.x + rays_i] = tex.addr[((int)texPos & 63) * tex.size.x + tex_x];
		drawStart++;
		texPos += steptex;
	}
	for (int i = drawEnd + 1; i < SCREEN_H; i++)
		img.addr[i * img.size.x + rays_i] = mlx->tex.f_color;
}

int	raycast(t_mlx *mlx)
{
	int			rays_i;
	int			side;
	float		perpWallDist;
	t_fcoord	rayDir;

	rays_i = 0;
   // struct timeval te; 
    //gettimeofday(&te, NULL); // get current time
    //long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
	while (rays_i < SCREEN_W)
	{
		rayDir = get_ray_dir(rays_i, mlx->game.p);
		perpWallDist = loop_rays(mlx->game, rayDir, &side);
		draw(
			SCREEN_H / perpWallDist, mlx, rays_i,
			get_side_tex(side, rayDir, mlx->tex),
			get_tex_x(side, rayDir, perpWallDist, mlx->game.p),
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
