#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

typedef struct s_gnllist
{
    char *buf;
    struct s_gnllist *next;
} t_gnllist;

char *get_next_line(int fd);
void create_list(int fd, t_gnllist **list);
void append(t_gnllist **list, char *buf);
char *get_line(t_gnllist *list);
void	dealloc(t_gnllist **list, t_gnllist *clean_node, char *buf);
int found_newline(t_gnllist *list);
t_gnllist *find_last_node(t_gnllist *list);
int count_char(t_gnllist *list);
void cpy_str(t_gnllist *list, char *line);
void	polish_list(t_gnllist **list);

#endif
