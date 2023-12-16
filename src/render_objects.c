#include "../includes/minirt.h"

double find_sp_hit(t_elem obj, t_vec coor, t_vec dir_vec)
{
    t_vec sphere2camera;
    double t;

    sphere2camera = vec_sub(coor, obj.coor);
    double a = vec_dot(dir_vec, dir_vec);
    double b = 2 * vec_dot(sphere2camera, dir_vec);
    double c = vec_dot(sphere2camera, sphere2camera) - (obj.radius * obj.radius);
    double d = b * b - 4 * a * c;
    if (d >= 0)
    {
        t = (-b - sqrt(d)) / (2 * a);
        if (t < 0)
            t = (-b + sqrt(d)) / (2 * a);
        return t;
    }
    return -1;}

void render_sphere(t_world *world, t_elem obj, t_fcolor *color, double *closest)
{
    t_vec dir_vec;

    dir_vec = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    double hit_distance = find_sp_hit(obj, world->camera.coor, dir_vec);
    if (hit_distance >= 0 && (hit_distance <= closest[1] || closest[1] == -1))
    {
        *color = obj.color;
        closest[0] = *obj.obj;
        closest[1] = hit_distance;
    }
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
        if (t > 0 && cylinder_hight_ok(obj, coor, dir_vec, t))
            return t;
        else
        {
            t = (-b + sqrt(d)) / (2 * a);
            if (t > 0 && cylinder_hight_ok(obj, coor, dir_vec, t))
                return t;
        }
    }
    return -1;
}

void render_cylinder(t_world *world, t_elem obj, t_fcolor *color, double *closest)
{
    t_vec dir_vec = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    double hit_distance = find_cy_hit(obj, world->camera.coor, dir_vec);
    if (hit_distance >= 0 && (hit_distance <= closest[1] || closest[1] == -1))
    {
        *color = obj.color;
        closest[0] = *obj.obj;
        closest[1] = hit_distance;
    }
}

double find_pl_hit(t_elem obj, t_vec coor, t_vec dir_vec)
{

    double a = vec_dot(obj.vec, obj.coor) - vec_dot(obj.vec, coor);
    double b = vec_dot(obj.vec, dir_vec);
    if (a == 0)
        return 0;
    else if (b != 0 && (a / b > 0))
        return (a / b);
    return -1;
}

void render_plane(t_world *world, t_elem obj, t_fcolor *color, double *closest)
{
    double hit_distance;
    t_vec dir_vec = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    hit_distance = find_pl_hit(obj, world->camera.coor, dir_vec);
    if (hit_distance >= 0 && (hit_distance <= closest[1] || closest[1] == -1))
    {
        *color = obj.color;
        closest[0] = *obj.obj;
        closest[1] = hit_distance;
    }
}

int render_objects(t_world *world)
{
    t_elem *obj;
    t_fcolor color;
    double closest[2];

    color = color_init(0, 0, 0);
    closest[0] = 0;
    closest[1] = -1;
    obj = world->objs;
    while (obj)
    {
        if (!ft_strncmp(obj->obj, "sp", 2))
            render_sphere(world, *obj, &color, closest);
        else if (!ft_strncmp(obj->obj, "pl", 2))
            render_plane(world, *obj, &color, closest);
        else if (!ft_strncmp(obj->obj, "cy", 2))
            render_cylinder(world, *obj, &color, closest);
        obj = obj->next;
    }
    render_ambient(world->ambient, &color);
    return create_rgb_from_fcolor(color);
}
