/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:05:48 by jorgfern          #+#    #+#             */
/*   Updated: 2023/09/28 15:13:06 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	ssize_t	i;
	char	*ptr;

	i = ft_strlen(str);
	ptr = 0;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			ptr = &(((char *)str)[i]);
		--i;
	}
	return (ptr);
}
