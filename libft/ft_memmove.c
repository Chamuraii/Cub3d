/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:42:04 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/15 15:33:25 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nul(char *a, char *b, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		a[i] = b[i];
		i ++;
	}
}

void	*ft_memmove(void *str, const void *str2, size_t size)
{
	size_t	i;
	char	*a;
	char	*b;

	a = (char *)str;
	b = (char *)str2;
	if (!str && !str2)
		return (0);
	i = size;
	if (a > b)
	{
		while (i > 0)
		{
			a[i - 1] = b[i - 1];
			i --;
		}
	}
	else
	{
		nul(str, (char *)str2, size);
	}
	return (str);
}

/*  int main()
{
	char str[] = "mipmip";
	char str2[] = "bonbon";
	ft_memmove(str, str2, 5);
	printf("%s", str);
	return 0;
} 
  */
