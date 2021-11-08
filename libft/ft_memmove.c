/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:01:26 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/04/08 12:50:46 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	puttab(char *destcpy, char *srccpy, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		destcpy[i] = srccpy[i];
		i++;
	}
}

void	puttaboverlap(char *destcpy, char *srccpy, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		destcpy[i - 1] = srccpy[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destcpy;
	char	*srccpy;

	if (src == NULL && dest == NULL)
		return (NULL);
	destcpy = (char *)dest;
	srccpy = (char *)src;
	if (destcpy > srccpy)
		puttaboverlap(destcpy, srccpy, n);
	else
		puttab(destcpy, srccpy, n);
	return (destcpy);
}
