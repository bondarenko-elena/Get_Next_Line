/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olbondar <olbondar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 19:25:25 by olbondar          #+#    #+#             */
/*   Updated: 2018/05/19 20:21:44 by olbondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		lst_add_back(t_list **alst, t_list *new)
{
	t_list *tmp;

	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_list_my	*if_fd_exist(t_list_my **data, int fd)
{
	t_list_my *lst;

	lst = *data;
	while (lst != NULL && lst->fd != fd)
	{
		lst = lst->next;
	}
	return (lst);
}

// ft_strstr, ft_strjoin
char		*get_data(t_list_my **data, int fd)
{
	t_list_my	*curr;
	char		*head;
	char		*tail;
	char		*tmp;

	curr = if_fd_exist(data, fd);
	if (curr->content == NULL)
		return (NULL);
	if ((tail = ft_strstr((char*)curr->content, "\n")) != NULL)
	{
		STRCHECK(head = ft_strsub((char*)curr->content,
				0, (curr->content_size - ft_strlen(++tail) - 2))));
		tmp = curr->content;
		curr->content = (ft_strlen(tail) == 0) ? NULL : (void *)ft_strdup(tail);
		curr->content_size = ft_strlen(tail) + 1;
		free(tmp);
	}
	else
	{
		STRCHECK(!(head = ft_strdup((char *)curr->content)));
		free(curr->content);
		curr->content = NULL;
		curr->content_size = 0;
	}
	return (head);
}

int			check_data(t_list_my **data, char *buff, int fd)
{
	t_list_my	*current;
	char		*tmp;

	current = if_fd_exist(data, fd);
	if (current == NULL)
	{
		current = (t_list_my*)ft_lstnew((void*)buff, (ft_strlen(buff) + 1));
		if (current == NULL)
			return (-1);
		current->fd = fd;
		ft_lstadd_back((t_list**)data, (t_list*)current);
	}
	else
	{
		tmp = ft_strjoin((char*)current->content, buff);
		if (tmp == NULL)
			return (-1);
		free(current->content);
		current->content = (void*)tmp;
		current->content_size = ft_strlen(tmp) + 1;
	}
	if (ft_strstr((char*)current->content, "\n") != NULL)
		return (1);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char				buff[BUFF_SIZE + 1];
	static t_list_my	*data = NULL;
	int					ret;
	int					res;

	if (line == NULL || BUFF_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (fd < 0 || ret < 0 )
			return (-1);
		buff[ret] = '\0';
		if ((res = check_data(&data, buff, fd)) == 1)
		{
			if ((*line = get_data(&data, fd)) != NULL)
			return (1);
		}
		else
			return (-1);
	}
	return (0);
}
