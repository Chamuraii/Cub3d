/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:36:35 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/12 15:37:48 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(long int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		count = 1;
	else
	{
		if (nb < 0)
		{
			nb *= -1;
			count++;
		}
		while (nb > 0)
		{
			nb /= 10;
			count++;
		}
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = n;
	i = ft_digit_count(nb);
	str = malloc(i * sizeof(char) + 1);
	if (!(str))
		return (0);
	str[i--] = 0;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
