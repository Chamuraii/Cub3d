/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:34:10 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/01 21:37:38 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	char	*r;

	r = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			r = &((char *)str)[i];
		i++;
	}
	if (str[i] == (char)ch)
		r = &((char *)str)[i];
	if (ch == '\0')
		r = &((char *)str)[i];
	return (r);
}
