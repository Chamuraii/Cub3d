/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:05:45 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/01 20:07:13 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(char *str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		str[i] = '\0';
		i ++;
	}
}

/* int main()
{
	char str[] = "mipmip";
	ft_bzero(str, 6);
	return 0;
} 
 */