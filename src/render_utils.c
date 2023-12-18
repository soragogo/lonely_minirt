#include "../includes/minirt.h"

double find_sp_hit(t_elem obj, t_vec coor, t_vec dir_vec)
{
    t_vec sphere2camera;
    double t;

    sphere2camera = vec_sub(coor, obj.coor);
    // double a = vec_dot(dir_vec, dir_vec);
    double b = 2 * vec_dot(sphere2camera, dir_vec);
    double c = vec_dot(sphere2camera, sphere2camera) - (obj.radius * obj.radius);
    double d = b * b - 4 * c;
    if (d >= 0)
    {
        t = (-b - sqrt(d)) / 2;
        if (t <= 0)
            t = (-b + sqrt(d)) / 2;
        if (t > 0.00001)
        {
            return t;
        }
    }
    return -1;
}

double find_cy_hit(t_elem obj, t_vec coor, t_vec dir_vec)
{
    double a = t_2_coefficient(obj, dir_vec);
    double b = t_1_coefficient(obj, coor, dir_vec);
    double c = t_0_coefficient(obj, coor);
    double d = b * b - 4 * a * c;
    double t;
    if (a != 0 && d >= 0)
    {
        t = (-b - sqrt(d)) / (2 * a);
        if (t > 0.00001 && cylinder_hight_ok(obj, coor, dir_vec, t))
            return t;
        else
        {
            t = (-b + sqrt(d)) / (2 * a);
            if (t > 0.00001 && cylinder_hight_ok(obj, coor, dir_vec, t))
                return t;
        }
    }
    return -1;
}


double find_pl_hit(t_elem obj, t_vec coor, t_vec dir_vec)
{

    double a = vec_dot(obj.vec, obj.coor) - vec_dot(obj.vec, coor);
    double b = vec_dot(obj.vec, dir_vec);
    if (a == 0)
        return 0;
    else if (b != 0 && (a / b > 0.00001))
        return (a / b);
    return -1;
}
