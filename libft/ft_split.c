/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:15:36 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/15 14:14:22 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countw(char const *s, char c)
{
	int	i;
	int	cw;
	int	j;

	j = 0;
	while (s[j])
		j ++;
	cw = 1;
	i = 0;
	if (s[0] == c)
		cw --;
	if (s[j - 1] == c)
		cw --;
	while (s[i])
	{
		if (s[i] != c)
			i++;
		else
		{
			while (s[i] == c)
				i ++;
			cw ++;
		}
	}
	return (cw);
}

static char	*word(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((countw(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

/* int main()
{
	char c = ' ';
	char const *s = " Je suis    Lucas    . ";
	printf("%d \n", countw(s, c));
	return 0;
} */