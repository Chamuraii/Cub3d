/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:36:37 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/15 17:54:11 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
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
		return (i);
	}
	return (0);
}
