/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:05:48 by jorgfern          #+#    #+#             */
/*   Updated: 2023/09/29 13:27:25 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	ssize_t	i;

	i = (ssize_t)ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (&(((char *)str)[i]));
		--i;
	}
	return (0);
}
