/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/10 12:14:39 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mmap[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,1,1},
	{1,0,1,0,0,0,0,1,0,1},
	{1,0,0,1,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,1,0,0,1},
	{1,0,1,0,0,0,0,1,0,1},
	{1,1,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,1}
};

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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
	t_data		img;

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	while (rays_i < SCREEN_W)
	{
		double		cameraX = 2 * rays_i / ((double)SCREEN_W) - 1;;
		t_fcoord	rayDir;
		t_fcoord	sideDist;
		t_fcoord	deltaDist;

		rayDir.x = pDir.x + plane.x * cameraX;
		rayDir.y = pDir.y + plane.y * cameraX;

		deltaDist.x = (rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x); 
		deltaDist.y = (rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y); 
		double	perpWallDist;

		t_icoord	step;
		t_icoord	map;
		int			hit = 0;
		int			side;

		map.x = (int)pPos.x; 
		map.y = (int)pPos.y;

		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (pPos.x - map.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map.x + 1.0 - pPos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			step.y = -1;
			sideDist.y = (pPos.y - map.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0 - pPos.y) * deltaDist.y;
		}

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
			if (mmap[map.x][map.y] > 0)
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

		int	lineHeight = (int)(SCREEN_H / perpWallDist); 
		int	drawStart = -lineHeight / 2 + SCREEN_H / 2;
		if (drawStart < 0) drawStart = 0;
		int	drawEnd = lineHeight / 2 + SCREEN_H / 2;
		if (drawEnd >= SCREEN_H)
			drawEnd = SCREEN_H - 1;
	while (drawStart <= drawEnd)
		set_px(&img, (t_icoord){rays_i, drawStart++}, color);
	rays_i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->black->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	return 0;
}