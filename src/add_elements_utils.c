#include "../includes/minirt.h"





void get_vec_from_str(t_vec *vec, char *str, int is_vector)
{
    char *end;
    double val[3];
    int i;
    // 未実装
    check_vec_syntax(str);
    i = 0;
    while (i < 3)
    {
        end = ft_strchr(str, ',');
        if (i == 2)
            end = str + strlen(str); // 文字列の終端を指すように設定
        printf("get vec from this: %s\n", str);
        printf("Get val from[%s]\n", str);
        val[i] = atod(str);
        printf("val[%d]: %f\n", i, val[i]);
        if (is_vector && (val[i] < -1 || 1 < val[i]))
            ft_error("Vector or coordinate syntax error");
        if (end)
            str = end + 1;
        i++;
    }
    vec->x = val[0];
    vec->y = val[1];
    vec->z = val[2];
}



void get_color_from_str(t_fcolor *color, char *str)
{
    char *end;
    int val[3];
    int i;

    check_color_syntax(str);
    i = 0;
    while (i < 3)
    {
        end = ft_strchr(str, ',');
        if (i == 2)
            end = str + strlen(str); // 文字列の終端を指すように設定
        printf("get color from this: %s\n", str);
        val[i] = ft_atoi(str);
        printf("val[%d]: %d\n", i, val[i]);
        if (val[i] < 0 || 255 < val[i])
            ft_error("Color syntax error");
        if (end)
            str = end + 1;
        i++;
    }
    color->r = val[0];
    color->g = val[1];
    color->b = val[2];
}
