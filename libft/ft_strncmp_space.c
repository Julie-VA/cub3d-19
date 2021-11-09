/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:51:37 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/08 14:52:04 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_strncmp_space(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	size_t			k;
	unsigned char	*s1cpy;
	unsigned char	*s2cpy;

	s1cpy = (unsigned char *)s1;
	s2cpy = (unsigned char *)s2;
	i = 0;
	j = 0;
	k = 0;
	if (n == 0)
		return (0);
	while (s2[j] && s2[j] == ' ')
		j++;
	i = j;
	while (i < (n + j - 1) && s1cpy[k] == s2cpy[i] && s1cpy[k] && s2cpy[i])
	{
		i++;
		k++;
	}
	if (s1cpy[k] != s2cpy[i])
		return (s1cpy[k] - s2cpy[i]);
	else
		return (0);
}
