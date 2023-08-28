/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:19:06 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/01 20:07:51 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str, const void *str2, size_t size)
{
	size_t	i;

	if (!str && !str2)
		return (0);
	i = 0;
	while (i < size)
	{
		((unsigned char *)str)[i] = ((unsigned char *)str2)[i];
		i ++;
	}
	return (str);
}
