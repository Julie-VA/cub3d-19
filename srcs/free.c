/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:14:03 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/18 15:14:14 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_file(t_file *file)
{
	int	i;

	i = 0;
	while (file->raw_file[i])
		free(file->raw_file[i++]);
	free(file->raw_file);
	free(file);
	return (1);
}

int	free_all_but_mini(t_file *file)
{
	int	i;

	i = 0;
	while (file->raw_file[i])
		free(file->raw_file[i++]);
	free(file->raw_file);
	i = 0;
	while (file->map[i])
		free(file->map[i++]);
	free(file->map);
	free(file);
	return (1);
}

int	free_all(t_file *file)
{
	int	i;

	i = 0;
	free_all_but_mini(file);
	while (file->minimap[i])
		free(file->minimap[i++]);
	free(file->minimap);
	return (1);
}
