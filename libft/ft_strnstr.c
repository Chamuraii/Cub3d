/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:49:51 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/15 18:15:21 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (to_find[i] || !to_find || !str)
		i ++;
	if (i > n)
		return (NULL);
	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (str);
	while ((str[i] != '\0') && (i < n))
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0' && (i + j) < n)
			j++;
		if (to_find[j] == '\0' && i < n)
		{
			return ((char *)str + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}

/* int main()
{
	char str[12] = "yyyhkj.com";
	char ch = 'hkj';
	char a = *ft_strnstr(str, ch, 5);
	printf ("%d", a);
	return 0;
}  
  */