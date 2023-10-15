/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_areCharInStr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:05:11 by jorgfern          #+#    #+#             */
/*   Updated: 2023/04/25 18:05:18 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_areCharInStr(char *str, char *characters)
{
	int	i;
	int j;

	i = 0;
	while (characters[i])
	{
		j = 0;
		while (str[j])
			if (str[j++] == characters[i])
				return (1);
		++i;
	}
	return (0);
}