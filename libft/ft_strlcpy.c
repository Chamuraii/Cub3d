/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:38:18 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/01 20:08:35 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *str, const char *str2, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while ((i < size -1) && (str2[i] != '\0'))
		{
			str[i] = str2[i];
			i ++;
		}
		str[i] = 0;
	}
	while (str2[i])
		i ++;
	return (i);
}

/* int main()
{
	char str[] = "rioe";
	char str2[] = "mememe";
	size_t euh = ft_strlcpy(str, str2, 5);
	printf("%zu",euh);
	size_t euh2 = strlcpy(str, str2, 5);
	printf("%zu",euh2);
	return 0;
} */
