/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:28:10 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/01 20:08:12 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(unsigned char *)(str + i) = (unsigned char )c;
		i ++;
	}
	return (str);
}

/* 
int main()
{
	char str[] = "mipmip";
	ft_memset(str, '-', 6);
	return 0;
}  */