/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:46:33 by jchamak           #+#    #+#             */
/*   Updated: 2022/10/16 14:23:30 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if ((*del) && lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}

/* int main()
{
	t_list	lst;

	ft_lstdelone(&lst, NULL);
}
 */