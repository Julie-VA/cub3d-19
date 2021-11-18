/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:41:23 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/18 17:06:18 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		return (tex.e);
	else if (side == 0 && ray_dir.x > 0)
		return (tex.w);
	else if (side == 1 && ray_dir.y > 0)
		return (tex.s);
	return (tex.n);
}

/*
	draw_i: x -> drawStart, y -> drawEnd
*/
void	draw(int lineHeight, t_tex tex_s, unsigned int *buff, unsigned int *tex)
{
	t_icoord	draw_i;
	float		steptex;
	float		texpos;
	int			i;

	i = 0;
	draw_i = (t_icoord){-lineHeight / 2 + SCREEN_H / 2,
		lineHeight / 2 + SCREEN_H / 2};
	if (draw_i.x < 0)
		draw_i.x = 0;
	if (draw_i.y >= SCREEN_H)
		draw_i.y = SCREEN_H - 1;
	steptex = 1.0 * 64 / lineHeight;
	texpos = (draw_i.x - SCREEN_H / 2 + lineHeight / 2) * steptex;
	while (i < draw_i.x)
		buff[i++ *SCREEN_W] = tex_s.c_color;
	while (i <= draw_i.y)
	{
		buff[i++ *SCREEN_W] = tex[((int)texpos & 63) * 64];
		texpos += steptex;
	}
	while (i < SCREEN_H)
		buff[i++ *SCREEN_W] = tex_s.f_color;
}
