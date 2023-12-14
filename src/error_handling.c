#include "../includes/minirt.h"

void ft_error(char *log)
{
    ft_putstr_fd("Error: ", STDERR_FILENO);
    ft_putstr_fd(log, STDERR_FILENO);
    exit (EXIT_FAILURE);
}

void check_period_syntax(char *str)
{
    int period_count;

    period_count = 0;
    // printf("str: %s\n", str);
    while (*str)
    {
        if (*str == '.')
        {
            if (!*(str - 1) || !*(str + 1))
                ft_error("Vector or coordinate syntax error");
            else if (!ft_isdigit(*(str - 1)) || !ft_isdigit(*(str + 1)))
                ft_error("Vector or coordinate syntax error");
            period_count ++;
        }
        if (*str == ',')
            period_count = 0;
        if (period_count > 1)
            ft_error("Wrong_format");
        str++;
    }
}

void check_comma_syntax(char *str)
{
    int comma_count;

    comma_count = 0;
    // printf("str: %s\n", str);
    while (*str)
    {
        if (*str == ',')
            comma_count ++;
        str++;
    }
    if (comma_count != 2)
        ft_error("Wrong format");
}

void check_vec_syntax(char *str)
{
    char *tmp;
    bool first;

    tmp = str;
    first = true;
    // printf("str: %s\n", str);
    check_comma_syntax(str);
    check_period_syntax(str);
    while (*tmp)
    {
        if (*tmp == '-' && !first)
            ft_error("Vector or coordinate syntax error");
        else if (!ft_isdigit(*tmp)
            && *tmp != ',' && *tmp != '.' && *tmp != '-')
            ft_error("Vector or coordinate syntax error");
        first = false;
        if (*tmp == ',')
            first = true;
        tmp++;
    }
}


void check_color_syntax(char *str)
{
    char *tmp;
    bool first;

    tmp = str;
    first = true;
    check_comma_syntax(str);
    while (*tmp)
    {
        if (*tmp == '0' && first
            && *(tmp + 1) && ft_isdigit(*(tmp + 1)))
            ft_error("Color syntax error");
        if (!ft_isdigit(*tmp) && *tmp != ',')
            ft_error("Color syntax error");
        first = false;
        if (*tmp == ',')
            first = true;
        tmp++;
    }
}
