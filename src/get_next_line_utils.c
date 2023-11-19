#include "../includes/get_next_line.h"
#include "../libft/libft.h"

int found_newline(t_gnllist *list)
{
    int i;
    if (!list)
        return (0);
    while (list)
    {
        i = 0;
        while (list->buf[i])
        {
            if (list->buf[i] == '\n')
                return (1);
            i++;
        }
        list = list->next;
    }
    return (0);
}

void	polish_list(t_gnllist **list)
{
	t_gnllist	*last_node;
	t_gnllist	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	clean_node = ft_calloc(sizeof(t_gnllist), 1);
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->buf[i] && last_node->buf[i] != '\n')
		++i;
	while (last_node->buf[i] && last_node->buf[++i])
		buf[k++] = last_node->buf[i];
	buf[k] = '\0';
	clean_node->buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

void cpy_str(t_gnllist *list, char *line)
{
    int i;
    int k;

    if (!list)
        return ;
    k = 0;
    while (list)
    {
        i = 0;
        while (list->buf[i] && i < BUFFER_SIZE)
        {
            // printf("cpying list->buf[%d]: %c\n", i, list->buf[i]);
            if (list->buf[i] == '\n')
            {
                // line[k++] = '\n';
                line[k] = '\0';
                return ;
            }
            line[k++] = list->buf[i++];
        }
        list = list->next;
    }
}

int count_char(t_gnllist *list)
{
    int len = 0;
    int i = 0;

    while (list)
    {
        i = 0;
        while (list->buf[i])
        {
            if (list->buf[i] == '\n')
            {
                len ++;
                return (len);
            }
            i++;
            len++;
        }
        list = list->next;
    }
    return (len);
}

t_gnllist *find_last_node(t_gnllist *list)
{
    if (!list)
        return (NULL);
    while (list->next)
    {
        list = list->next;
    }
    // printf("list: %s\n", list->buf);
    return (list);

}
