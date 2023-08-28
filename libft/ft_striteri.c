/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:51:57 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/07 17:57:14 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (s && f)
	{
		a = ft_strlen(s);
		while (a > b)
		{
			(*f)(b, s);
			s ++;
			b ++;
		}
	}
}
