#include "../includes/minirt.h"

double t_2_coefficient(t_world *world, t_elem obj)
{
    t_vec b = obj.vec;
    t_vec d = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    double q = vec_sum(d);

    return (q * q + 1 - 2 * q * vec_dot(b,d));
}

double t_1_coefficient(t_world *world, t_elem obj)
{
    t_vec a = obj.coor;
    t_vec b = obj.vec;
    t_vec c = world->camera.coor;
    t_vec d = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    double q = -vec_sum(b) + vec_sum(c) - vec_dot(a, b);

    return (2 * ((vec_dot(a, b) - vec_dot(b, c) + 1) * vec_sum(d)
                -q * vec_dot(b, d) + vec_dot(c, d) - vec_dot(a, d)));
}

double t_0_coefficient(t_world *world, t_elem obj)
{
    t_vec a = obj.coor;
    t_vec b = obj.vec;
    t_vec c = world->camera.coor;
    double q = -vec_sum(b) + vec_sum(c) - vec_dot(a, b);

    return (q * q + vec_dot(c, c) + vec_dot(a, a)
            + 2 * (q * (vec_dot(a, b) - vec_dot(b, c)) - vec_dot(c, a)));
}

bool cylinder_hight_ok(t_world *world, t_elem obj, double t)
{
    t_vec a = obj.coor;
    t_vec b = obj.vec;
    t_vec c = world->camera.coor;
    t_vec d = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    double s = vec_sum(d) * t - vec_sum(b) + vec_sum(c) - vec_dot(a, b);
    if (t < 0)
        return (false);
    else if (s < 0 || obj.hgt < s)
        return (false);
    return (true);
}
