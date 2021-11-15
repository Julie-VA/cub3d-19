/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/15 15:05:09 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_bg_color(char *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(color, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	printf("rgb=%d\n", (unsigned int)(65536 * r + 256 * g + b));
	return (0);
}

unsigned int	get_pixel(t_data *data, t_icoord coord, int side)
{
	char	*color;
	int		offset;
	(void)side;

	offset = coord.y * data->line_len + coord.x * (data->bpp / 8);
	color = data->addr + offset;
	// printf("color=%d\n", *(unsigned int *)color);
	// if (!side)
		return (*(unsigned int *)color);
	// else
	// 	return (*(unsigned int *)color / 2);
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

	for (int i = 0; i < mlx->buff->size.x; i++)
		for (int j = 0; j < mlx->buff->size.y; j++)
		{
			set_px(mlx->buff, (t_icoord) {i, j}, get_bg_color(mlx->file->f_color));	
		}
	while (rays_i < SCREEN_W)
	{
		double		cameraX = 2 * rays_i / ((double)SCREEN_W) - 1;;
		t_fcoord	rayDir;
		t_fcoord	sideDist;
		t_fcoord	deltaDist;

		rayDir.x = pdir.x + pplane.x * cameraX;
		rayDir.y = pdir.y + pplane.y * cameraX;

		deltaDist.x = (rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x); 
		deltaDist.y = (rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y); 
		double	perpWallDist;

		t_icoord	step;
		t_icoord	map;
		int			hit = 0;
		int			side;

		map.x = (int)ppos.x; 
		map.y = (int)ppos.y; 

		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (ppos.x - map.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map.x + 1.0 - ppos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			step.y = -1;
			sideDist.y = (ppos.y - map.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0 - ppos.y) * deltaDist.y;
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
			wall_x = ppos.y + perpWallDist * rayDir.y;
		else
			wall_x = ppos.x + perpWallDist * rayDir.x;
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
			if (side == 0 && rayDir.x < 0)
				set_px(mlx->buff, (t_icoord){rays_i, drawStart++}, get_pixel(mlx->purple, (t_icoord) {tex_x, (int)texPos & 63}, side));
			else if (side == 0 && rayDir.x > 0)
				set_px(mlx->buff, (t_icoord){rays_i, drawStart++}, get_pixel(mlx->blue, (t_icoord) {tex_x, (int)texPos & 63}, side));
			else if (side == 1 && rayDir.y > 0)
				set_px(mlx->buff, (t_icoord){rays_i, drawStart++}, get_pixel(mlx->brick, (t_icoord) {tex_x, (int)texPos & 63}, side));
			else
				set_px(mlx->buff, (t_icoord){rays_i, drawStart++}, get_pixel(mlx->grey, (t_icoord) {tex_x, (int)texPos & 63}, side));
			texPos += steptex;
		}
		rays_i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->buff->img, 0, 0);
	return 0;
}
