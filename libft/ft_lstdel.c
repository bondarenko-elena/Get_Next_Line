/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olbondar <olbondar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 17:02:08 by olbondar          #+#    #+#             */
/*   Updated: 2017/11/25 17:02:24 by olbondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*lst;

	lst = *alst;
	while (lst)
	{
		del(lst->content, lst->content_size);
		free(lst);
		lst = lst->next;
	}
	*alst = NULL;
}
