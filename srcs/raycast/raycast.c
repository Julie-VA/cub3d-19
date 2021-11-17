/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/17 13:47:52 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel(t_data data, t_icoord coord)
{
	char	*color;
	int		offset;

	offset = coord.y * data.line_len + coord.x * (data.bpp / 8);
	color = data.addr + offset;
	return (*(unsigned int *)color);
}

void	set_px(t_data data, t_icoord coord, unsigned int color)
{
	char	*dst;
	int		offset;

	if (coord.x < 0 || coord.x >= SCREEN_W || coord.y < 0 || coord.y >= SCREEN_H)
		return;
	offset = coord.y * data.line_len + coord.x * (data.bpp / 8);
	dst = data.addr + offset;
	*(unsigned int *)dst = color;
}

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

int	foo()
{
	float		perpWallDist;
}

int	loop_rays(t_game game, t_fcoord rayDir)
{
	t_fcoord	deltaDist;
	int			side;

	deltaDist.x = (rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x); 
	deltaDist.y = (rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y); 

	side = launch_rays(game, deltaDist, rayDir);
	return side;
}

int	launch_rays(t_game game, t_fcoord deltaDist, t_fcoord rayDir)
{
	int	hit = 0;
	t_icoord	step;
	int			side;
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
			side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			map.y += step.y;
			side = 1;
		}
		if (game.map[map.y][map.x] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = sideDist.x - deltaDist.x;
	else
		perpWallDist = sideDist.y - deltaDist.y;
	return (side);
}

int	get_tex_x(int side, t_fcoord rayDir, int perpWallDist, t_player *p)
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

int	raycast(t_mlx *mlx)
{
	int				rays_i = 0;

	while (rays_i < SCREEN_W)
	{
		t_fcoord	rayDir;
		t_fcoord	sideDist;
		int			side;
		float		perpWallDist;

		rayDir = get_ray_dir(rays_i, mlx->game.p);
		side = loop_rays(mlx->game, rayDir);
		float	lineHeight = (int)(SCREEN_H / perpWallDist); 
		int	drawStart = -lineHeight / 2 + SCREEN_H / 2;


		if (drawStart < 0) drawStart = 0;

		int	drawEnd = lineHeight / 2 + SCREEN_H / 2;

		if (drawEnd >= SCREEN_H)
			drawEnd = SCREEN_H - 1;

		float steptex = 1.0 * 64 / lineHeight;
		float texPos = (drawStart - SCREEN_H / 2 + lineHeight / 2) * steptex;

		for (int i = 0; i < drawStart; i++)
			set_px(mlx->buff, (t_icoord){rays_i, i}, mlx->tex.c_color);

		t_data	tex;

		if (side == 0 && rayDir.x < 0)
			tex = mlx->tex.purple;
		else if (side == 0 && rayDir.x > 0)
			tex = mlx->tex.blue;
		else if (side == 1 && rayDir.y > 0)
			tex = mlx->tex.brick;
		else
			tex = mlx->tex.grey;
		while (drawStart <= drawEnd)
		{
			set_px(mlx->buff, (t_icoord){rays_i, drawStart}, get_pixel(tex, (t_icoord) {tex_x, (int)texPos & 63}));
			drawStart++;
			texPos += steptex;
		}
		for (int i = drawEnd + 1; i < SCREEN_H; i++)
			set_px(mlx->buff, (t_icoord){rays_i, i}, mlx->tex.f_color);
		rays_i++;
	}
	//print_minimap(mlx->file, mlx->buff, mlx->tex.bg_c);
	mlx_put_image_to_window(mlx->vars.mlx, mlx->vars.win, mlx->buff.img, 0, 0);
	return 0;
}
