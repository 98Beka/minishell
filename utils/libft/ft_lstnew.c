/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hveiled <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:15:58 by hveiled           #+#    #+#             */
/*   Updated: 2020/11/07 14:46:34 by hveiled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(*newlist));
	if (!newlist)
		return (NULL);
	if (content == NULL)
		newlist->content = NULL;
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}
