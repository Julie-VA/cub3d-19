/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:47:35 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/17 14:55:51 by vneirinc         ###   ########.fr       */
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