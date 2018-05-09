#include "get_next_line.h"

static t_list			*get_data(t_list **data, int fd)
{
	t_list				*tmp;

	tmp = *data;
	while (tmp != NULL)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(data, tmp);
	tmp = *data;
	return (tmp);
}

int	check(int fd, char **line)
{
	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	return (0);
}

char	*strjoin_ch(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !c)
		return (NULL);
	s1_len = ft_strlen(s1);
	new_str = ft_strnew(s1_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}

int			copy_until(char **dst, char *src, char c)
{
	int		i;
	int		count;
	int		pos;

	i = -1;
	count = 0;
	while (src[++i])
		if (src[i] == c)
			break ;
	pos = i;
	if (!(*dst = ft_strnew(i)))
		return (0);
	while (src[count] && count < i)
	{
		if (!(*dst = strjoin_ch(*dst, src[count])))
			return (0);
		count++;
	}
	return (pos);
}

int						get_next_line(const int fd, char **line)
{
	char				buff[BUFF_SIZE + 1];
	static t_list		*data;
	t_list				*current;
	int					ret;
	int					i;

	if (check(fd, line) != 0)
		return (-1);

	current = get_data(&data, fd);
	
	if(!(*line = ft_strnew(1)))
		return(-1);
		
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if(!(current->content = ft_strjoin(current->content, buf)))
			return (-1);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(current->content))
		return (0);
	i = copy_until(line, curr->content, '\n');
	if (i < (int)ft_strlen(current->content))
		current->content += (i + 1);
	else
		ft_strclr(current->content);
	return (1);
}
