/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:49:16 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/02 17:20:42 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	i;
	size_t	t;

	i = 0;
	t = ft_strlen(s);
	if (t == 0 || start >= (unsigned int)t)
		return (ft_strdup(""));
	if (len > t)
		tab = (char *) malloc((t + 1) * sizeof(char));
	else
		tab = (char *) malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (i < len && s[start + i])
	{
		tab[i] = s[start + i];
		i ++;
	}
	tab[i] = '\0';
	return (tab);
}

/* int main()
{
	char s[] = "1234567890"; 
	unsigned int start = 56;
	size_t len = 3;
	printf("%s \n",ft_substr(s, start, len));
	return(0);
}  */