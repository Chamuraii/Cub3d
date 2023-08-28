/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:26:56 by jchamak           #+#    #+#             */
/*   Updated: 2023/03/01 13:54:39 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pd(int n, int fd, int i);
int	pu(unsigned int n, int fd, int i);
int	px(unsigned int n, int fd, int c, int i);
int	ft_hexa2(unsigned long n, int fd, int i);
int	ft_putchar_fd2(char c, int fd);

int	ps(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &(str[i]), 1);
		i++;
	}
	return (i);
}

int	pp(unsigned long str)
{
	int	i;

	if (!str)
	{
		write(1, "0x0", 3);
		return (3);
	}
	ft_putchar_fd2('0', 1);
	ft_putchar_fd2('x', 1);
	i = 2;
	i = ft_hexa2(str, 1, i);
	return (i);
}

int	types(va_list args, char c)
{
	int		count;
	char	temp;

	count = 0;
	if (c == 'c')
	{
		temp = (va_arg(args, int));
		write(1, &temp, 1);
		count++;
	}
	else if (c == 's')
		count += ps(va_arg(args, char *));
	else if (c == 'p')
		count += pp(va_arg(args, unsigned long));
	else if (c == 'd' || c == 'i')
		count += pd(va_arg(args, int), 1, 0);
	else if (c == 'u')
		count += pu(va_arg(args, unsigned int), 1, 0);
	else if (c == 'x')
		count += px(va_arg(args, int), 1, 1, 0);
	else if (c == 'X')
		count += px(va_arg(args, int), 1, 0, 0);
	else if (c == '%')
		count += ft_putchar_fd2('%', 1);
	return (count);
}

int	ft_printf(const char *trucs, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(args, trucs);
	while (trucs[i] != '\0')
	{
		while (trucs[i])
		{
			if (trucs[i] == '%')
				j += types(args, trucs[++i]);
			else
				j += ft_putchar_fd2(trucs[i], 1);
			i++;
		}
	}
	va_end(args);
	return (j);
}
