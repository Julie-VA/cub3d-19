/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/10 16:44:28 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	get_pixel(t_data *data, t_icoord coord)
{
	char	*color;
	int		offset;

	offset = coord.y * data->line_len + coord.x * (data->bpp / 8);
	color = data->addr + offset;
	return (*(unsigned int *)color);
}

void	set_px(t_data *data, t_icoord coord, unsigned int color)
{
	char	*dst;
	int		offset;

	if (coord.x < 0 || coord.x >= SCREEN_W || coord.y < 0 || coord.y >= SCREEN_H)
		return;
	offset = coord.y * data->line_len + coord.x * (data->bpp / 8);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

int	raycast(t_mlx *mlx)
{
	int			rays_i = 0;

	printf("%f\n", mlx->player.pos.y);
	printf("%f\n", mlx->player.pos.x);
	while (rays_i < SCREEN_W)
	{
		double		cameraX = 2 * rays_i / ((double)SCREEN_W) - 1;;
		t_fcoord	rayDir;
		t_fcoord	sideDist;
		t_fcoord	deltaDist;

		rayDir.x = mlx->player.dir.x + mlx->player.plane.x * cameraX;
		rayDir.y = mlx->player.dir.y + mlx->player.plane.y * cameraX;

		deltaDist.x = (rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x); 
		deltaDist.y = (rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y); 
		double	perpWallDist;

		t_icoord	step;
		t_icoord	map;
		int			hit = 0;
		int			side;

		map.x = (int)mlx->player.pos.x; 
		map.y = (int)mlx->player.pos.y; 

		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (mlx->player.pos.x - map.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map.x + 1.0 - mlx->player.pos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			step.y = -1;
			sideDist.y = (mlx->player.pos.y - map.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0 - mlx->player.pos.y) * deltaDist.y;
		}

		printf("cc\n");
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
			printf("%d %d\n", map.x, map.y);
			if (mlx->file->map[map.y][map.x] == '1')
				hit = 1;
		}
		int color;
		if (side == 0)
		{
			color = 225;
			perpWallDist = sideDist.x - deltaDist.x;
		}
		else
		{
			color = 225/2;
			perpWallDist = sideDist.y - deltaDist.y;
		}

		double wall_x;

		if (side == 0)
			wall_x = mlx->player.pos.y + perpWallDist * rayDir.y;
		else
			wall_x = mlx->player.pos.x + perpWallDist * rayDir.x;
		wall_x -= floor(wall_x);

		int	tex_x = wall_x * 64;

		if(side == 0 && rayDir.x > 0) tex_x = 64 - tex_x - 1;
		if(side == 1 && rayDir.y < 0) tex_x = 64 - tex_x - 1;

		double	lineHeight = (int)(SCREEN_H / perpWallDist); 
		int	drawStart = -lineHeight / 2 + SCREEN_H / 2;


		if (drawStart < 0) drawStart = 0;

		int	drawEnd = lineHeight / 2 + SCREEN_H / 2;

		if (drawEnd >= SCREEN_H)
			drawEnd = SCREEN_H - 1;

		double steptex = 1.0 * 64 / lineHeight;
		double texPos = (drawStart - SCREEN_H / 2 + lineHeight / 2) * steptex;

		while (drawStart <= drawEnd)
		{
			set_px(mlx->buff, (t_icoord){rays_i, drawStart++}, get_pixel(mlx->tex, (t_icoord) {tex_x, (int)texPos & 63}));
			texPos += steptex;
		}
		rays_i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->buff->img, 0, 0);
	return 0;
}