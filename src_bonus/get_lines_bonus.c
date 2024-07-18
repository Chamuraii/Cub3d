/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:14:38 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:46:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_next_line_no_nl(int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (str)
		if (str[0])
			if (str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = 0;
	return (str);
}

char	*get_line_map(char ***matrix, char **str, int fd, int *j)
{
	(*matrix)[(*j)++] = ft_strdup(*str);
	free(*str);
	return (get_next_line_no_nl(fd));
}
