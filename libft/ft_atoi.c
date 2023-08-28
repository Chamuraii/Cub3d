/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:34:00 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/02 16:06:25 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	signe(int sign);

int	ft_atoi(const char *str)
{
	unsigned int	n;
	int				i;
	int				sign;

	sign = 0;
	n = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
	i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (ft_isdigit(str[i]) == 0 && ft_isdigit(str[i + 1]) == 0)
			return (0);
		if (str[i] == '-')
			sign--;
	i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
	n = n * 10 + (str[i] - '0');
	i++;
	}
	sign = signe(sign);
	return (sign * n);
}

static int	signe(int sign)
{
	if (sign % 2 == 0)
		sign = 1;
	else
		sign = -1;
	return (sign);
}
