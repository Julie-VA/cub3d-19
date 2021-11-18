/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:30 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/18 13:07:46 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_player	player_init(t_file *file)
{
	t_player	p;

	p.pos = (t_fcoord){file->p_pos_x + 0.5, file->p_pos_y + 0.5};
	if (file->p_ori == 'N')
	{
		p.dir = (t_fcoord){0, -1};
		p.plane = (t_fcoord){-0.66, 0};
	}
	else if (file->p_ori == 'S')
	{
		p.dir = (t_fcoord){0, 1};
		p.plane = (t_fcoord){0.66, 0};
	}
	else if (file->p_ori == 'W')
	{
		p.dir = (t_fcoord){1, 0};
		p.plane = (t_fcoord){0, -0.66};
	}
	else if (file->p_ori == 'E')
	{
		p.dir = (t_fcoord){-1, 0};
		p.plane = (t_fcoord){0, 0.66};
	}
	return (p);
}

t_player	*game_init(t_file *file)
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (!p)
		return (NULL);
	*p = player_init(file);
	return (p);
}
