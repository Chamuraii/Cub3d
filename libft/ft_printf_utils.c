/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:10:41 by jchamak           #+#    #+#             */
/*   Updated: 2023/03/01 13:55:51 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd2(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	pd(int n, int fd, int i)
{
	if (n == -2147483648)
	{
		i += ft_putchar_fd2('-', fd);
		i += ft_putchar_fd2('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		n = -n;
		i += ft_putchar_fd2('-', fd);
	}
	if (n >= 10)
	{
		i = pd(n / 10, fd, i);
		i = pd(n % 10, fd, i);
	}
	else
		i += ft_putchar_fd2(n + '0', fd);
	return (i);
}

int	pu(unsigned int n, int fd, int i)
{
	if (n >= 10)
	{
		i = pu(n / 10, fd, i);
		i = pu(n % 10, fd, i);
	}
	else
		i += ft_putchar_fd2(n + '0', fd);
	return (i);
}

int	px(unsigned int n, int fd, int c, int i)
{
	if (n >= 16)
	{
		i = px(n / 16, fd, c, i);
		i = px(n % 16, fd, c, i);
	}
	else
	{
		if (n < 10)
			i += ft_putchar_fd2(n + '0', fd);
		else
		{
			if (c == 0)
				i += ft_putchar_fd2(n + '7', fd);
			else
				i += ft_putchar_fd2(n + 'W', fd);
		}
	}
	return (i);
}

int	ft_hexa2(unsigned long n, int fd, int i)
{
	if (n >= 16)
	{
		i = ft_hexa2(n / 16, fd, i);
		i = ft_hexa2(n % 16, fd, i);
	}
	else
	{
		if (n < 10)
			i += ft_putchar_fd2(n + '0', fd);
		else
			i += ft_putchar_fd2(n + 'W', fd);
	}
	return (i);
}
