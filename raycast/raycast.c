/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:58:20 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/08 16:34:51 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldmap[24][24] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	set_px(t_data *data, t_icoord coord, unsigned int color)
{
	char	*dst;
	int		offset;

	offset = coord.y * data->line_len + coord.x * (data->bpp / 8);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

int	raycast(char **wmap, t_data *img)
{
	t_fcoord	pPos = (t_fcoord) {12, 2};
	t_fcoord	pDir = (t_fcoord) {-1, 0};
	t_fcoord	plane = (t_fcoord) {0, 0.66};
	int			rays_i = 0;


	(void)wmap;
	while (rays_i < SCREEN_W)
	{
		float		cameraX = 2 * rays_i / ((float)SCREEN_W) - 1;
		t_fcoord	rayDir;
		t_fcoord	sideDist;
		t_fcoord	deltaDist;

		rayDir.x = pDir.x + plane.x * cameraX;
		rayDir.y = pDir.y + plane.y * cameraX;

		deltaDist.x = (rayDir.x == 0) ? __FLT_MAX__ : fabs(1 / rayDir.x); 
		deltaDist.y = (rayDir.y == 0) ? __FLT_MAX__ : fabs(1 / rayDir.y); 

		float	perpWallDist;

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
				map.y += step.x;
				side = 1;
			}

			if (worldmap[map.x][map.y] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDist.x - deltaDist.x;
		else
			perpWallDist = sideDist.y - deltaDist.y;

		int	lineHeight = (int)(SCREEN_H / perpWallDist); 
		int	drawStart = -lineHeight / 2 + SCREEN_H / 2;
		if (drawStart < 0) drawStart = 0;
		int	drawEnd = lineHeight / 2 + SCREEN_H / 2;
		if (drawEnd >= SCREEN_H)
			drawEnd = SCREEN_H - 1;
	int color;
      switch(worldmap[map.x][map.y])
      {
        case 1:  color = create_trgb(0, 25, 0, 12);  break; //red
        case 2:  color = 255;  break; //green
        case 3:  color = 10024;   break; //blue
        case 4:  color = -90;  break; //white
        default: color = 12; break; //yellow
      }
      if (side == 1) {color = color / 2;}
		while (drawStart <= drawEnd)
			set_px(img, (t_icoord){rays_i, drawStart++}, color);
		rays_i++;
	}
	return 0;
}