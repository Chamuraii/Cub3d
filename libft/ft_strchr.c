/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:54:32 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/01 20:08:15 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return ((char *)(str + i));
		i ++;
	}
	if (str[i] == (char)ch)
		return ((char *)(str + i));
	return (0);
}

/* 
int	main()
{
	char str[12] = "yyyhkj.com";
	char ch = 'h';
	char a = *ft_strchr(str, ch);
	printf ("%d", a);
	return 0;
}
*/