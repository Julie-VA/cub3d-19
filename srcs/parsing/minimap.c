/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:42:36 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/18 13:36:35 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_group	mini_loop_x(t_file *file, char **mini, t_group v, t_icoord mamu)
{
	v.xy.x = 0;
	while (file->map[v.xy.y][v.xy.x])
	{
		if (file->map[v.xy.y][v.xy.x] == '1')
			mini[v.ij.y + (v.xy.y * mamu.y)][v.ij.x + (v.xy.x * mamu.y)] = '1';
		else if (file->map[v.xy.y][v.xy.x] == ' ')
			mini[v.ij.y + (v.xy.y * mamu.y)][v.ij.x + (v.xy.x * mamu.y)] = ' ';
		else
			mini[v.ij.y + (v.xy.y * mamu.y)][v.ij.x + (v.xy.x * mamu.y)] = '0';
		if (v.ij.x == mamu.y - 1)
		{
			v.ij.x = 0;
			v.xy.x++;
			continue ;
		}
		v.ij.x++;
	}
	return (v);
}

char	**minimap_loop(t_file *file, char **mini, t_group v, t_icoord mamu)
{
	while (file->map[v.xy.y])
	{
		v = mini_loop_x(file, mini, v, mamu);
		while (v.xy.x < mamu.x)
		{
			if (v.ij.x == mamu.y)
			{
				v.ij.x = 0;
				v.xy.x++;
				continue ;
			}
			mini[v.ij.y + (v.xy.y * mamu.y)][v.ij.x + (v.xy.x * mamu.y)] = ' ';
			v.ij.x++;
		}
		mini[v.ij.y + (v.xy.y * mamu.y)][v.xy.x * mamu.y] = '\0';
		if (v.ij.y == mamu.y - 1)
		{
			v.ij.y = 0;
			v.xy.y++;
			continue ;
		}
		v.ij.y++;
	}
	mini[v.xy.y * mamu.y] = NULL;
	return (mini);
}

char	**set_minimap(t_file *file)
{
	int			maxl;
	char		**minimap;
	int			multipl;
	t_group		vars;
	t_icoord	maxlmultipl;

	vars.xy.x = 0;
	vars.xy.y = 0;
	vars.ij.x = 0;
	vars.ij.y = 0;
	minimap = alloc_minimap(file->map, &maxl, &multipl);
	if (!minimap)
		return (NULL);
	maxlmultipl.x = maxl;
	maxlmultipl.y = multipl;
	minimap = minimap_loop(file, minimap, vars, maxlmultipl);
	return (minimap);
}

t_icoord	print_minimap(char **minimap, t_data buff, unsigned int bg_c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (minimap[y])
	{
		x = 0;
		while (minimap[y][x])
		{
			if (minimap[y][x] == '1')
				buff.addr[y * buff.size.x + x] = 0x11000000;
			else if (minimap[y][x] == '0')
				buff.addr[y * buff.size.x + x] = bg_c;
			x++;
		}
		y++;
	}
	return ((t_icoord){x, y});
}
