/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:42:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/16 15:48:37 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_maxl(char **map)
{
	int	x;
	int	y;
	int	len;

	x = 0;
	y = 0;
	len = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > len)
			len = x;
		y++;
	}
	return (len);
}

t_icoord	print_mini_map(t_file *file, t_data *buff, unsigned int grey)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x])
		{
			if (file->map[y][x] == '1')
				set_px(buff, (t_icoord){i + (x * 5), j + (y * 5)}, 0);
			else
				set_px(buff, (t_icoord){i + (x * 5), j + (y * 5)}, grey);
			if (i == 4)
			{
				i = 0;
				x++;
				continue ;
			}
			i++;
		}
		if (j == 4)
		{
			j = 0;;
			y++;
			continue ;
		}
		j++;
	}
	return ((t_icoord){x * 5, y * 5});
}
