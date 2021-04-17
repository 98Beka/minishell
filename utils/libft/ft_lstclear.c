/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:23:09 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/11 15:04:43 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*begin;

	if (!*lst)
		return ;
	while (*lst)
	{
		begin = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = begin;
	}
	*lst = NULL;
}
