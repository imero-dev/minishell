/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 02:07:33 by ivromero          #+#    #+#             */
/*   Updated: 2024/01/18 13:07:11 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstmapnode(t_list **lst, void *(*f)(void *), void (*del)(void *),
		t_list **new_list)
{
	t_list	*node;
	void	*content;

	content = f((*lst)->content);
	node = ft_lstnew(content);
	if (!node)
		return (ft_lstclear(new_list, del), del(content), 0);
	ft_lstadd_back(new_list, node);
	*lst = (*lst)->next;
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
		if (!ft_lstmapnode(&lst, f, del, &new_list))
			return (NULL);
	return (new_list);
}
