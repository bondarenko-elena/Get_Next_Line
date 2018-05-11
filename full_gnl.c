#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

# define BUFF_SIZE 42

typedef struct        s_list
{
    void            *content;
    size_t            content_size;
    struct s_list    *next;
}                    t_list;

void	ft_strclr(char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		s[i] = '\0';
		i++;
	}
}

size_t    ft_strlen(const char *s)
{
    size_t size;

    size = 0;
    while (s[size] != '\0')
    {
        size++;
    }
    return (size);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t    i;
    size_t    j;
    size_t    length;
    char    *str;

    i = 0;
    if (s1 == NULL || s2 == NULL)
        return (NULL);
    length = ft_strlen(s1) + ft_strlen(s2);
    str = (char*)malloc(length + 1);
    if (str == NULL)
        return (NULL);
    while (s1[i] != '\0')
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j] != '\0')
    {
        str[i++] = s2[j++];
    }
    str[i] = '\0';
    return (str);
}

char    *ft_strnew(size_t size)
{
    char    *str;
    size_t    i;

    i = 0;
    str = (char*)malloc(size + 1);
    if (str == NULL)
        return (NULL);
    while (i < size)
    {
        str[i] = '\0';
        i++;
    }
    str[i] = '\0';
    return (str);
}

void    ft_lstadd(t_list **alst, t_list *new)
{
    if (alst)
    {
        new->next = *alst;
        *alst = new;
    }
}

void	*ft_memalloc(size_t size)
{
	size_t			i;
	unsigned char	*buff;

	i = 0;
	buff = (unsigned char *)malloc(size);
	if (buff == NULL)
		return (NULL);
	while (i < size)
	{
		buff[i] = 0;
		i++;
	}
	return (buff);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	const char	*ret;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
	{
		i++;
	}
	if (s[i] != (char)c)
		return (NULL);
	else
		ret = &s[i];
	return ((char *)ret);
}

t_list    *ft_lstnew(const void *content, size_t content_size)
{
    t_list    *new;

    new = NULL;
    if ((new = (t_list*)ft_memalloc(sizeof(t_list))) != NULL)
    {
        if (content != NULL)
        {
            new->content = ft_memalloc(content_size);
            if (new->content == NULL)
                return (NULL);
            ft_memcpy(new->content, content, content_size);
            new->content_size = content_size;
        }
        else
        {
            new->content = NULL;
            new->content_size = 0;
        }
        new->next = NULL;
    }
    return (new);
}

////////////////////////////////////////////////////////

char    *strjoin_ch(char const *s1, char c)
{
    char    *new_str;
    size_t    i;
    size_t    s1_len;

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

int            copy_until(char **dst, char *src, char c)
{
    int        i;
    int        count;
    int        pos;

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

static t_list            *get_data(t_list **data, int fd)
{
    t_list                *tmp;

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

int                        get_next_line(const int fd, char **line)
{
    char                buff[BUFF_SIZE + 1];
    static t_list        *data;
    t_list                *current;
    int                    ret;
    int                    i;

    if (fd < 0 || line == NULL || BUFF_SIZE < 1 || read(fd, buff, 0) < 0)
        return (-1);

    current = get_data(&data, fd);
    
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
    if (ret < BUFF_SIZE && !ft_strlen(current->content))
        return (0);
    i = copy_until(line, current->content, '\n');
    if (i < (int)ft_strlen(current->content))
        current->content += (i + 1);
    else
        ft_strclr(current->content);
    return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		puts(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
}
