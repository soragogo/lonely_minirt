#include "../includes/minirt.h"

double atod_itg(char **str)
{
    double ret;
    char *tmp;
    tmp = *str;

    ret = 0;
    if (*tmp == '0'
        && *(tmp + 1) && ft_isdigit(*(tmp + 1)))
        ft_error("Wrong format in number");
    while (*tmp && *tmp != '.' && *tmp != ',')
    {
        if (DBL_MAX / 10 < ret + *tmp - '0')
            ft_error("Number too small or too big");
        ret = (ret + *tmp - '0') * 10;
        tmp++;
    }
    ret /= 10;
    if (*tmp == '.')
        *str = tmp + 1;
    else
        *str = NULL;
    printf("itg: %f\n", ret);
    return (ret);
}

double atod_frct(char *str)
{
    int devide;
    double ret;

    devide = 0;
    ret = 0;
    while (*str && *str != ',')
    {
        if (DBL_MAX / 10 < ret + *str - '0')
            ft_error("Number too small or too big");
        ret = (ret + *str - '0') * 10;
        str++;
        devide += 1;
    }
    ret /= 10;
    while (devide--)
        ret /= 10;
    printf("frct: %f\n", ret);
    return (ret);
}


double atod(char *str)
{
    double ret;
    double minus;
    char *tmp;

    minus = 1;
    ret = 0;
    if (*str == '-')
    {
        minus = -1;
        str++;
    }
    printf("atod before: %s\n", str);
    if (str == NULL || *str == '\0')
        ft_error("Wrong format");
    tmp = str;
    ret = atod_itg(&tmp);
    if (tmp)
        ret += atod_frct(tmp);
    //　未実装
    printf("str: %s\n", str);
    printf("atod result: %f\n", minus * ret);
    return (minus * ret);
}
