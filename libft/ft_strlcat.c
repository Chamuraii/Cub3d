/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:07:30 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/01 21:08:13 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;
	char	*s;
	size_t	res;

	s = (char *)src;
		lendst = ft_strlen(dst);
		lensrc = ft_strlen(s);
		i = 0;
		res = 0;
	if (size > lendst)
		res = lensrc + lendst;
	else
		res = lensrc + size;
	while (s[i] && (lendst + 1) < size)
	{
		dst[lendst] = s[i];
		lendst++;
		i++;
	}
	dst[lendst] = '\0';
	return (res);
}
/*  int main()
{
	char str[] = "rioe";
	char str2[] = "mememe";
	size_t euh = ft_strlcat(str, str2, 5);
	printf("%zu",euh);
	size_t euh2 = strlcat(str, str2, 5);
	printf("%zu",euh2);
	return 0;
} */