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
    double c = vec_dot(sphere2camera, sphere2camera) - (obj.radius * obj.radius);
    double d = b * b - 4 * a * c;
    if (d >= 0)
    {
        t = (-b - sqrt(d)) / (2 * a);
        if (t < 0)
            t = (-b + sqrt(d)) / (2 * a);
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

    if (a == 0)
    {
        *color = create_rgb_from_fcolor(obj.color);
        return 0;
    }
    else if (b != 0 && (a / b > 0))
    {
        if (a / b <= closest || closest == -1)
        {
            *color = create_rgb_from_fcolor(obj.color);
            return (a / b);
        }
    }
    return (closest);
}

double q_func(double s_2, double s_1, double s_0, double x)
{
    return (s_2 * x * x + s_1 * x + s_0);
}

double render_cylinder(t_world *world, t_elem obj, int *color, double closest)
{
//     円筒の底面の中心をPとする。
//     上面の中心をQとする。レイと、円筒が交差する条件は以下の二つを満たした時。
//     ① 線分PQとの距離が円筒の半径以下である。
//     ② ①の交点から直線PQに垂線を下ろした時に、その交点が線分PQの中にあること。
//     これをコードに落とせばおけ！

//     coreの座標について A + sB
//     rayについて C + tD
//     (x - (A + sB))^2 + (y - (A + sB))^2 + (z - (A + sB))^2  = r^2
//     (C + tD - (A + sB))^2 + (C + tD - (A + sB))^2 + (C + tD - (A + sB))^2  = r^2
//     tについて解いて a*t^2 + b*t + c = 0 の形に直すと、
//     係数は、
//     a = D_to_D
//     b = 2((-B_dot_D)s + D_dot_C - A_dot_D)
//     c = (B_dot_B)s^2 + C_dot_C + A_dot_A +2(A_dot_B - B_dot_C)s + +2(-A_dot_C) - r^2
//     紙とペン欲しい…。
//     0 <= s <= obj.hgt の時
//     判別式が正となるような解sがあれば良い。
//     （s = 0と s = obj.radiusのところだけ調べれば良くね）場合分けして
//     tが正の解を持つか。
        t_vec a = obj.coor;
        t_vec b = obj.vec;
        t_vec c = world->camera.coor;
        t_vec d = vec_normalize(vec_sub(world->camera.scr_pos, world->camera.coor));
        int crossed;

        crossed = -1;
        //sの係数を出すと、
        double s_2 = vec_dot(b, d) * vec_dot(b, d) - 1;// - vec_dot(d, d) * vec_dot(b, b);
        double s_1 = 2 * vec_dot(b , d) * (vec_dot(a,d) - vec_dot(c, d))
                    + 2 * vec_dot(d , d) * (vec_dot(b,c) - vec_dot(a,b));
        double s_0 = (vec_dot(c, d) - vec_dot(a, d)) * (vec_dot(c, d) - vec_dot(a, d))
                    + vec_dot(d, d) * (vec_dot(a,c) - vec_dot(c, c) - vec_dot(a,a) + obj.radius * obj.radius);
        if (s_1 < 0 || obj.hgt < (s_1 / 2) || s_2 == 0)
        {
            if (q_func(s_2, s_1, s_0, 0) >= 0 ||  q_func(s_2, s_1, s_0, vec.hgt) >= 0)
                atari;
        }
        else
        {
            if (q_func(s_2, s_1, s_0, s_1 / 2) * q_func(s_2, s_1, s_0, 0) <= 0
                || q_func(s_2, s_1, s_0, s_1 / 2) * q_func(s_2, s_1, s_0, hgt) <= 0)
                atari
        }
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
            closest = render_sphere(world, *obj, &color, closest);
        }
        else if (!ft_strncmp(obj->obj, "pl", 2))
        {
            closest = render_plane(world, *obj, &color, closest);
        }
        // else if (!ft_strncmp(obj->obj, "cy", 2))
        // {
        //     closest = render_cylinder(world, *obj, &color, closest);
        // }
        obj = obj->next;
        index++;
    }
    // if (closest != -1)
    //     printf("color: %d\n", color);
    return color;
}
