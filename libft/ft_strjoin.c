/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:03:19 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/02 18:48:32 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	h;
	char	*cpy;

	h = 0;
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	cpy = (char *) ft_calloc (i + j + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	while (h < i)
	{
		cpy[h] = s1[h];
		h ++;
	}
	while (h <= j + i)
	{
		cpy[h] = s2[h - i];
		h ++;
	}
	return (cpy);
}
