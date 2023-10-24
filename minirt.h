#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;


t_vec          vec_init(double x, double y, double z);
t_vec          vec_add(t_vec a, t_vec b);
t_vec          vec_sub(t_vec a, t_vec b);
t_vec          vec_mult(t_vec a, double b);
double         vec_dot(t_vec a, t_vec b);
t_vec          vec_cross(t_vec a, t_vec b);
double         vec_mag(t_vec a);
t_vec          vec_normalize(t_vec a);
int                get_vec_from_str(t_vec *vec, char *str);




#endif
