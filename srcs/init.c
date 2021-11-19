/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneirinc <vneirinc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:20:30 by vneirinc          #+#    #+#             */
/*   Updated: 2021/11/19 10:22:46 by vneirinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_player	p_init(t_file *file)
{
	t_player	p;

	p.pos = (t_fcoord){file->p_pos_x + 0.5, file->p_pos_y + 0.5};
	if (file->p_ori == 'N')
	{
		p.dir = (t_fcoord){0, -1};
		p.plane = (t_fcoord){0.66, 0};
	}
	else if (file->p_ori == 'S')
	{
		p.dir = (t_fcoord){0, 1};
		p.plane = (t_fcoord){-0.66, 0};
	}
	else if (file->p_ori == 'W')
	{
		p.dir = (t_fcoord){1, 0};
		p.plane = (t_fcoord){0, 0.66};
	}
	else if (file->p_ori == 'E')
	{
		p.dir = (t_fcoord){-1, 0};
		p.plane = (t_fcoord){0, -0.66};
	}
	return (p);
}

t_player	*player_init(t_file *file)
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (!p)
		return (NULL);
	*p = p_init(file);
	return (p);
}

void	destroy_tex(t_tex *tex, void *mlx)
{
	if (tex->n.img)
		mlx_destroy_image(mlx, tex->n.img);
	else
		return ;
	if (tex->s.img)
		mlx_destroy_image(mlx, tex->s.img);
	else
		return ;
	if (tex->e.img)
		mlx_destroy_image(mlx, tex->e.img);
	else
		return ;
	if (tex->w.img)
		mlx_destroy_image(mlx, tex->w.img);
	else
		return ;
}

int	tex_init(t_file *file, void *mlx, t_tex *tex)
{
	tex->n.img = mlx_xpm_file_to_image(mlx, file->n_texture,
			&(tex->n.size.x), &(tex->n.size.y));
	tex->s.img = mlx_xpm_file_to_image(mlx, file->s_texture,
			&(tex->s.size.x), &(tex->s.size.y));
	tex->e.img = mlx_xpm_file_to_image(mlx, file->e_texture,
			&(tex->e.size.x), &(tex->e.size.y));
	tex->w.img = mlx_xpm_file_to_image(mlx, file->w_texture,
			&(tex->w.size.x), &(tex->w.size.y));
	if (!tex->n.img || !tex->s.img || !tex->e.img || !tex->w.img)
	{
		printf("Error wrong texture file name\n");
		destroy_tex(tex, mlx);
		return (0);
	}
	tex->n.addr = (unsigned int *)mlx_get_data_addr(tex->n.img,
			&tex->n.bpp, &tex->n.line_len, &tex->n.endian);
	tex->s.addr = (unsigned int *)mlx_get_data_addr(tex->s.img,
			&tex->s.bpp, &tex->s.line_len, &tex->s.endian);
	tex->e.addr = (unsigned int *)mlx_get_data_addr(tex->e.img,
			&tex->e.bpp, &tex->e.line_len, &tex->e.endian);
	tex->w.addr = (unsigned int *)mlx_get_data_addr(tex->w.img,
			&tex->w.bpp, &tex->w.line_len, &tex->w.endian);
	return (1);
}

void	*game_init(t_file *file)
{
	t_vars	vars;
	t_data	buff;
	t_tex	tex;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (NULL);
	buff.img = mlx_new_image(vars.mlx, SCREEN_W, SCREEN_H);
	if (!buff.img)
		return (NULL);
	buff.size = (t_icoord){SCREEN_W, SCREEN_H};
	buff.addr = (unsigned int *)mlx_get_data_addr(buff.img, &buff.bpp,
			&buff.line_len, &buff.endian);
	if (!tex_init(file, vars.mlx, &tex))
		return (NULL);
	vars.win = mlx_new_window(vars.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!hook_init(vars, tex, file, buff))
		return (NULL);
	return (vars.mlx);
}
