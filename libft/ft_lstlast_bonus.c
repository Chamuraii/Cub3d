/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:56:52 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/15 17:59:37 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;

	if (lst)
	{
		i = 1;
		while (lst->next != NULL)
		{
			lst = lst->next;
			i ++;
		}
		return (lst);
	}
	return (0);
}
