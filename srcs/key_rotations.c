/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:13:50 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/19 10:30:04 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_r(t_player *p, float old_dirx, float old_planex)
{
	p->dir.x = p->dir.x * cos(0.1) - p->dir.y * sin(0.1);
	p->dir.y = old_dirx * sin(0.1) + p->dir.y * cos(0.1);
	p->plane.x = p->plane.x * cos(0.1) - p->plane.y * sin(0.1);
	p->plane.y = old_planex * sin(0.1) + p->plane.y * cos(0.1);
}

void	key_l(t_player *p, float old_dirx, float old_planex)
{
	p->dir.x = p->dir.x * cos(-0.1) - p->dir.y * sin(-0.1);
	p->dir.y = old_dirx * sin(-0.1) + p->dir.y * cos(-0.1);
	p->plane.x = p->plane.x * cos(-0.1) - p->plane.y * sin(-0.1);
	p->plane.y = old_planex * sin(-0.1) + p->plane.y * cos(-0.1);
}
