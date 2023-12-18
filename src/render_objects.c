#include "../includes/minirt.h"



void render_sphere(t_world *world, t_elem obj, t_fcolor *color, t_info *closest)
{
    t_vec dir_vec;

    dir_vec = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    double hit_distance = find_sp_hit(obj, world->camera.coor, dir_vec);
    if (hit_distance >= 0 && (hit_distance <= closest->d || closest->d == -1))
    {
        *color = obj.color;
        closest->obj = obj;
        closest->d = hit_distance;
        closest->xed_pt = vec_add(world->camera.coor, vec_mult(dir_vec, hit_distance));
    }
}



void render_cylinder(t_world *world, t_elem obj, t_fcolor *color, t_info *closest)
{
    t_vec dir_vec = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    double hit_distance = find_cy_hit(obj, world->camera.coor, dir_vec, closest);
    if (hit_distance >= 0 && (hit_distance <= closest->d || closest->d == -1))
    {
        *color = obj.color;
        closest->obj = obj;
        closest->d = hit_distance;
        closest->xed_pt = vec_add(world->camera.coor, vec_mult(dir_vec, hit_distance));
    }
}


void render_plane(t_world *world, t_elem obj, t_fcolor *color, t_info *closest)
{
    double hit_distance;
    t_vec dir_vec = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
    hit_distance = find_pl_hit(obj, world->camera.coor, dir_vec);
    if (hit_distance >= 0 && (hit_distance <= closest->d || closest->d == -1))
    {
        *color = obj.color;
        closest->obj = obj;
        closest->d = hit_distance;
        closest->xed_pt = vec_add(world->camera.coor, vec_mult(dir_vec, hit_distance));
    }
}

// typedef struct s_info
// {
//     double d;
//     t_elem obj;
//     t_vec xed_pt;
//     t_vec to_light;
//     t_vec normal;
// } t_info;

int render_objects(t_world *world)
{
    t_elem *obj;
    t_fcolor color;
    // double closest[2];
    t_info closest;

    ft_bzero(&closest, sizeof(t_info));
    closest.side = 1;
    color = color_init(0, 0, 0);
    // closest[0] = 0;
    closest.d = -1;
    // closest[1] = -1;
    obj = world->objs;
    while (obj)
    {
        if (!ft_strncmp(obj->obj, "sp", 2))
            render_sphere(world, *obj, &color, &closest);
        else if (!ft_strncmp(obj->obj, "pl", 2))
            render_plane(world, *obj, &color, &closest);
        else if (!ft_strncmp(obj->obj, "cy", 2))
            render_cylinder(world, *obj, &color, &closest);
        obj = obj->next;
    }
    render_light(world, &closest, &color);
    return create_rgb_from_fcolor(color);
}
