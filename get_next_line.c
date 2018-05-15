#include "get_next_line.h"

char    *strjoin_ch(char const *s1, char c)
{
    size_t    i;
    size_t    length;
	char    *new_str;

    i = 0;
	if (s1 == NULL || c == NULL)
        return (NULL);
    length = ft_strlen(s1);
    str = (char*)malloc(length + 1);
    if (str == NULL)
        return (NULL);
    while (i < length)
	{
		*(str + i) = *(s1 + i);
		i++;
	}
    *(str + i) = c;
    return (str);
}

int            copy_until(char *src, char **dst, char c)
{
    int        i;
	int        position;
    int        count;

    i = 0;
    count = 0;
    while (src[i] != '\0')
	{
		if (src[i] == c)
            break ;
		i++;
	}
    position = i;
    if ((*dst = ft_strnew(i)) == NULL)
        return (0);
    while ((src[count] != '\0') && count < i)
    {
        if ((*dst = strjoin_ch(*dst, src[count])) == NULL)
            return (0);
        count++;
    }
    return (position);
}

static t_list            *get_current(t_list **data, int fd)
{
    t_list                *current;

    current = *data;
    while (current != NULL)
    {
        if ((int)current->content_size == fd)
            return (current);
        current = current->next;
    }
    current = ft_lstnew("\0", fd);
    ft_lstadd(data, current);
    current = *data;
    return (current);
}

int                        get_next_line(const int fd, char **line)
{
    char                buff[BUFF_SIZE + 1];
    static t_list        *data;
    t_list                *current;
    int                    ret;
    int                    i;

    if (fd < 0 || line == NULL || BUFF_SIZE < 1 || read(fd, buff, 0) < 0)
        return (-1);

    current = get_current(&data, fd);
    
//    if(!(*line = ft_strnew(1)))
//        return(-1);
        
    while ((ret = read(fd, buff, BUFF_SIZE)))
    {
        buff[ret] = '\0';
        if(!(current->content = ft_strjoin(current->content, buff)))
            return (-1);
        if (ft_strchr(buff, '\n'))
            break ;
    }
    if (ret < BUFF_SIZE && (ft_strlen(current->content) == 0))
        return (0);
    i = copy_until(current->content, line, '\n');
    if (i < (int)ft_strlen(current->content))
        current->content += (i + 1);
    else
        ft_strclr(current->content);
    return (1);
}
