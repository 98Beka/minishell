/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:07:42 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/07 18:41:13 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*lst_el;

	if (!lst || !*f)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		lst_el = ft_lstnew(f(lst->content));
		if (!lst_el)
		{
			ft_lstclear(&lst_el, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, lst_el);
		lst = lst->next;
	}
	return (new_lst);
}
