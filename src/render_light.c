#include "../includes/minirt.h"



t_vec caliculate_surface_normal(t_world *world, t_info *closest)
{
    t_elem obj;
    obj = closest->obj;
    if (!strncmp(obj.obj, "sp", 1))
    {
        return (vec_normalize(vec_sub(closest->xed_pt, obj.coor)));
    }
    else if (!strncmp(obj.obj, "pl", 1))
        return vec_normalize(obj.vec);
    else // if(!strncmp(obj.obj, "cy", 1))
    {
        t_vec d = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
        double s = - vec_dot(obj.coor,obj.vec)
                    + vec_dot(obj.vec, world->camera.coor)
                    + closest->d * vec_dot(obj.vec, d);
        t_vec core = vec_init(closest->obj.coor.x, closest->obj.coor.y, closest->obj.coor.z);
        core = vec_add(core, vec_mult(closest->obj.vec, s));
        return (vec_normalize(vec_sub(closest->xed_pt, core)));
    }
}

bool light_unreachable(t_world *world, t_info *closest)
{
    return false;
    if (strncmp(closest->obj.obj, "cy", 2))
        return false;
    t_vec normal;
    normal = caliculate_surface_normal(world, closest);
    double camera_pos;
    double light_pos;
    camera_pos = vec_dot(normal, world->camera.coor) - vec_dot(normal, closest->xed_pt);
    light_pos = vec_dot(normal, world->light.coor) - vec_dot(normal, closest->xed_pt);
    if (camera_pos * light_pos <= 0)
        return (true);
    else
        return (false);
}
bool is_shed(t_world *world, t_info *closest)
{
    t_vec coor =closest->xed_pt;
    t_vec dir_vec = closest->to_light;
    t_elem *obj;
    obj = world->objs;
    double obj_hit;

    obj_hit = -1;

    while (obj)
    {
        if (!ft_strncmp(obj->obj, "sp", 2))
            obj_hit = find_sp_hit(*obj, vec_add(coor, vec_mult(dir_vec, 0.00001)), dir_vec);
        else if (!ft_strncmp(obj->obj, "pl", 2))
            obj_hit = find_pl_hit(*obj, vec_add(coor, vec_mult(dir_vec, 0.00001)), dir_vec);
        else if (!ft_strncmp(obj->obj, "cy", 2))
        {
            obj_hit = find_cy_hit(*obj, vec_add(coor, vec_mult(dir_vec, 0.00001)), dir_vec);
        }
        if (obj_hit != -1 && obj_hit < vec_mag(vec_sub(world->light.coor, coor)))
        {
            return true;
        }
        obj = obj->next;
    }
    return false;
}



void light_init(double *rgb, double coefficient, double *original)
{
    if (original)
    {
        rgb[0] = coefficient * original[0];
        rgb[1] = coefficient * original[1];
        rgb[2] = coefficient * original[2];
    }
    else
    {
        ft_bzero(rgb, sizeof(double) * 3);
    }
}

void render_light(t_world *world, t_info *closest, t_fcolor *color)
{
    double rgb[3];
    closest->to_light = vec_normalize(vec_sub(world->light.coor, closest->xed_pt));
    light_init(rgb, 0, NULL);
    if (!light_unreachable(world, closest) && !is_shed(world, closest))
    {
        closest->normal = caliculate_surface_normal(world, closest);
        closest->normal = vec_mult(closest->normal, closest->side);
        double cos = vec_dot(closest->to_light, closest->normal);
        if (cos < 0)
            cos *= -1;
        else
            light_init(rgb, cos, world->light.rgb);
    }
    render_ambient(world->ambient, rgb);
    color->r *= rgb[0];
    color->g *= rgb[1];
    color->b *= rgb[2];
}
