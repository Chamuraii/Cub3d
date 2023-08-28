/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:48:37 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/02 17:07:36 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{	
	size_t	i;
	char	*cpy;

	i = 0;
	while (s[i])
		i ++;
	cpy = (char *) ft_calloc (i + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	cpy[i] = '\0';
	while (i > 0)
	{
		cpy[i - 1] = s[i - 1];
		i --;
	}
	return (cpy);
}
