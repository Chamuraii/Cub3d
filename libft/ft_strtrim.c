/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:04:18 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/10 19:50:27 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (0);
	while (ft_strchr(set, *s1) && *s1)
		s1 ++;
	while (s1[i])
		i ++;
	while (ft_strchr(set, s1[i]))
		i --;
	return (ft_substr(s1, 0, i + 1));
}
