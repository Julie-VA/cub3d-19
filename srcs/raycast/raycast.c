/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/10 16:40:57 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel(t_data *data, t_icoord coord, int side)
{
	char	*color;
	int		offset;

	offset = coord.y * data->line_len + coord.x * (data->bpp / 8);
	color = data->addr + offset;
	if (!side)
		return (*(unsigned int *)color);
	else
		return (*(unsigned int *)color / 2);
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

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->tex->bg, 0, 0);
	img.img = mlx_new_image(mlx->mlx, 1920, 1080);
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
			if (mlx->file->map[map.y][map.x] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDist.x - deltaDist.x;
		else
			perpWallDist = sideDist.y - deltaDist.y;

		double wall_x;

		if (side == 0)
			wall_x = pPos.y + perpWallDist * rayDir.y;
		else
			wall_x = pPos.x + perpWallDist * rayDir.x;
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
			set_px(&img, (t_icoord){rays_i, drawStart++}, get_pixel(mlx->tex, (t_icoord) {tex_x, (int)texPos & 63}, side));
			texPos += steptex;
		}
		rays_i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	return 0;
}
