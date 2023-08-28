/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:45:39 by jchamak           #+#    #+#             */
/*   Updated: 2022/09/23 16:58:43 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *) str == (unsigned char)c)
			return ((void *) str);
		str++;
	}
	return (0);
}

/* int main()
{
	char str[12] = "yyyhkj.com";
	int  ch = 'h';
	printf(" %p \n",ft_memchr(str, ch, 5));
	return 0;
}
  */