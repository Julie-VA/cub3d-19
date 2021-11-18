/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:13:50 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/18 16:13:54 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_r(t_game *g, float old_dirx, float old_planex)
{
	g->p->dir.x = g->p->dir.x * cos(0.1) - g->p->dir.y * sin(0.1);
	g->p->dir.y = old_dirx * sin(0.1) + g->p->dir.y * cos(0.1);
	g->p->plane.x = g->p->plane.x * cos(0.1) - g->p->plane.y * sin(0.1);
	g->p->plane.y = old_planex * sin(0.1) + g->p->plane.y * cos(0.1);
}

void	key_l(t_game *g, float old_dirx, float old_planex)
{
	g->p->dir.x = g->p->dir.x * cos(-0.1) - g->p->dir.y * sin(-0.1);
	g->p->dir.y = old_dirx * sin(-0.1) + g->p->dir.y * cos(-0.1);
	g->p->plane.x = g->p->plane.x * cos(-0.1) - g->p->plane.y * sin(-0.1);
	g->p->plane.y = old_planex * sin(-0.1) + g->p->plane.y * cos(-0.1);
}
