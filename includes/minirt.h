#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <unistd.h>

#include "../libft/libft.h"

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;


typedef struct s_fcolor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} t_fcolor;

typedef struct s_dlist
{
    t_vec coor;
    t_vec vec;
    unsigned char fov;
} t_dlist;

typedef struct s_elem
{
    char obj[3];
    t_vec coor;
    t_fcolor color;
    double diam;
    double hgt;
    struct s_elem *next;
} t_elem;

typedef struct s_world {
    void       *mlx;  // minilibx特有のやつ
    void       *win;  // minilibxのウィンドウを指すポインタ
    int        screen_width;
    int        screen_height;
    t_dlist camera;  // カメラ
    t_elem      *objs;  // 物体のリスト
    t_fcolor    ambient;  // 環境光の強度
    t_elem      light;  // 光源
}               t_world;

/*vector*/
t_vec          vec_init(double x, double y, double z);
t_vec          vec_add(t_vec a, t_vec b);
t_vec          vec_sub(t_vec a, t_vec b);
t_vec          vec_mult(t_vec a, double b);
double         vec_dot(t_vec a, t_vec b);
t_vec          vec_cross(t_vec a, t_vec b);
double         vec_mag(t_vec a);
t_vec          vec_normalize(t_vec a);
void            get_vec_from_str(t_vec *vec, char *str);

/*error_handling*/
void ft_error(char *log);




#endif
