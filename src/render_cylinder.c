#include "../includes/minirt.h"

double t_2_coefficient(t_elem obj, t_vec d)
{
    t_vec b = obj.vec;
    double p = vec_dot(b,d);

    return ( - p * p + 1);
}

double t_1_coefficient(t_elem obj, t_vec c, t_vec d)
{
    t_vec a = obj.coor;
    t_vec b = obj.vec;
    double q = - vec_dot(b, a) + vec_dot(b, c);

    return (2 * ((vec_dot(a, b) - vec_dot(b, c) + q) * vec_sum(d)
                -q * vec_dot(b, d) + vec_dot(c, d) - vec_dot(a, d)));
}

double t_0_coefficient(t_elem obj, t_vec c)
{
    t_vec a = obj.coor;
    t_vec b = obj.vec;
    double q = - vec_dot(b, a) + vec_dot(b, c);

    return (q * q + vec_dot(c, c) + vec_dot(a, a)
            + 2 * (q * (vec_dot(a, b) - vec_dot(b, c)) - vec_dot(c, a)) - obj.radius * obj.radius);
}

bool cylinder_hight_ok(t_elem obj, t_vec c, t_vec d, double t)
{
    t_vec a = obj.coor;
    t_vec b = obj.vec;
    double s = vec_dot(b,d) * t - vec_dot(b, a) + vec_dot(b, c);
    if (t < 0)
        return (false);
    else if (s < 0 || obj.hgt < s)
        return (false);
    return (true);
}
