/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modgnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:40:21 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/11/08 11:36:41 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_modstrlen(const char *s, int mod)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (mod == 1)
		while (s[i] && s[i] != '\n')
			i++;
	else
		while (s[i])
			i++;
	return (i);
}

char	*ft_modstrjoin(char const *s1, char const *s2)
{
	char	*str;
	int		lens1;
	int		lens2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	lens1 = ft_modstrlen(s1, 0);
	lens2 = ft_modstrlen(s2, 0);
	str = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, lens1);
	ft_memmove(str + lens1, s2, lens2);
	str[lens1 + lens2] = '\0';
	free((char *)s1);
	return (str);
}
