#include "../includes/get_next_line.h"
#include "../libft/libft.h"

void	dealloc(t_gnllist **list, t_gnllist *clean_node, char *buf)
{
	t_gnllist	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}



char *get_line(t_gnllist *list)
{
    char *line;
    int len;

    len = count_char(list);
    // printf("len: %d\n", len);

    line = ft_calloc(sizeof(char), len + 1);
    if (!line)
        return (NULL);
    cpy_str(list, line);
    return (line);
}



void append(t_gnllist **list, char *buf)
{
    t_gnllist *last_node;
    t_gnllist *new_node;

    last_node = find_last_node(*list);
    new_node = ft_calloc(sizeof(t_gnllist), 1);
    if (new_node == NULL)
        return ;
    if (last_node == NULL)
        *list = new_node;
    else
        last_node->next = new_node;
    new_node->buf = buf;
    new_node->next = NULL;
    // printf("new_node->buf [%s]\n", new_node->buf);

}




void create_list(int fd, t_gnllist **list)
{
    int bytesread = 0;
    char *buf;

    while (!found_newline(*list))
    {
        // puts("---");
        buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
        if (!buf)
            return ;
        bytesread = read(fd, buf, BUFFER_SIZE);
        if (!bytesread)
        {
            free(buf);
            return ;
        }
        buf[bytesread] = '\0';
        // printf("buf: [%s]\n", buf);
        append(list, buf);

    }
}





char *get_next_line(int fd)
{
    char *next_line;
    static t_gnllist *list;
    // puts("--------------func called---------");
    // list = NULL;
    if(fd < 0 || BUFFER_SIZE < 0 || read(fd, &next_line, 0) < 0)
        return (NULL);
    create_list(fd, &list);
    if (!list)
        return (NULL);
    next_line = get_line(list);
    // printf("next_line: %s\n", next_line);
    polish_list(&list);
    return (next_line);
}
