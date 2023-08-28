/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:24:51 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/16 16:29:15 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lt;

	if (!lst)
		return ;
	while (*lst)
	{
		lt = (*lst)->next;
		ft_lstdelone(*lst, (*del));
		*lst = lt;
	}
	*lst = NULL;
}
