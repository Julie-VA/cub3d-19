/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:51:09 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/04/03 16:51:09 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*srccpy;
	unsigned char	*destcpy;
	unsigned int	ccpy;
	size_t			i;

	ccpy = (unsigned char)c;
	srccpy = (unsigned char *)src;
	destcpy = (unsigned char *)dest;
	i = 0;
	while (srccpy && i < n && srccpy[i] != ccpy)
	{
		destcpy[i] = srccpy[i];
		i++;
	}
	if (i == n)
		return ((void *)0);
	if (srccpy[i] == ccpy)
	{
		destcpy[i] = srccpy[i];
		i++;
		return (destcpy + i);
	}
	return ((void *)0);
}
