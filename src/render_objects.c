#include "../includes/minirt.h"

double render_sphere(t_world *world, t_elem obj, int *color, double closest)
{
    t_vec sphere2camera;
    t_vec dir_vec;
    t_vec pos;
    double t;
    t = -1;

    pos = world->camera.scr_pos;
    sphere2camera = vec_sub(world->camera.coor, obj.coor);
    dir_vec = vec_normalize(vec_sub(pos, world->camera.coor));
    double a = vec_dot(dir_vec, dir_vec);
    double b = 2 * vec_dot(sphere2camera, dir_vec);
    double c = vec_dot(sphere2camera, sphere2camera) - (obj.diam * obj.diam);
    double d = b * b - 4 * a * c;
    if (d >= 0)
    {
        t = (-b - sqrt(d)) / (2 * a);
        if (t < 0)
            t = (-b + sqrt(d)) / (2 * a);
        // if (closest != -1)
            // printf("t: %f, closest: %f\n", t, closest);
        if ((t >= 0 && t <= closest) || closest == -1)
        {
            *color = create_rgb_from_fcolor(obj.color);
            return t;
        }
    }
    return closest;
}

double render_plane(t_world *world, t_elem obj, int *color, double closest)
{
    double a = vec_dot(obj.vec, obj.coor) - vec_dot(obj.vec, world->camera.coor);
    double b = vec_dot(obj.vec, world->camera.vec);

    if (!a)
    {
        *color = create_rgb_from_fcolor(obj.color);
        return 0;
    }
    else if (b && (a / b > 0))
    {
        if (a / b <= closest || closest == -1)
        {
            *color = create_rgb_from_fcolor(obj.color);
            return (a / b);
        }
    }
    return (closest);
}


int render_objects(t_world *world)
{
    t_elem *obj;
    int color;
    int index = 1;
    double closest;

    color = 0;
    closest = -1;
    obj = world->objs;
    while (obj)
    {
        if (!ft_strncmp(obj->obj, "sp", 2))
        {
            // printf("obj[%d]: %s %p\n",index, obj->obj, obj->obj);
            // printf("obj_vec x: %f,y: %f, z: %f\n", obj->coor.x, obj->coor.y, obj->coor.z);
            closest = render_sphere(world, *obj, &color, closest);
        }
        else if (!ft_strncmp(obj->obj, "pl", 2))
        {
            closest = render_plane(world, *obj, &color, closest);

        }
        obj = obj->next;
        index++;
    }
    // if (closest != -1)
    //     printf("color: %d\n", color);
    return color;
}
