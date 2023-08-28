/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:07:26 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/06 18:22:02 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	n;
	size_t	i;
	char	*str;

	i = 0;
	if (!s || !f)
		return (0);
	n = ft_strlen(s);
	str = (char *) malloc (sizeof(char) * (n + 1));
	if (!(str))
		return (0);
	while (i < n)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
