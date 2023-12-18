#include "../includes/minirt.h"

t_vec get_screen_horizon_vec(t_vec normal)
{
    t_vec ret;
    double mag;

    if (!normal.x && !normal.y)
    {
        ret.x = normal.z;
        ret.y = 0;
        ret.z = 0;
        return (ret);
    }
    ret.x = -normal.y;
    ret.y = normal.x;
    ret.z = 0;
    mag = vec_mag(ret);
    if (mag == 0)
        return (ret);
    ret.x /= mag;
    ret.y /= mag;
    ret.z /= mag;
    return (ret);
}

t_vec get_screen_vertical_vec(t_vec normal)
{
    t_vec ret;
    double mag;

    if (!normal.y && !normal.z)
    {
        ret.x = 0;
        ret.y = 0;
        ret.z = normal.x;
        return (ret);
    }
    ret.x = 0;
    ret.y = -normal.z;
    ret.z = normal.y;
    mag = vec_mag(ret);
    ret.x /= mag;
    ret.y /= mag;
    ret.z /= mag;
    return (ret);
}

t_vec get_screen_origin(t_world world)
{
    //カメラの中心座標を計算する

    int w_2 = 500 / 2; //world.win_w
    t_vec coor = world.camera.coor;
    t_vec vec = world.camera.vec;
    double fov = (double)world.camera.fov;
    t_vec ret;

    printf("camera.coor: %f, %f, %f\n", coor.x, coor.y, coor.z);
    printf("camera.vec: %f, %f, %f\n", vec.x, vec.y, vec.z);
    printf("camera.fov: %f\n", fov);
    printf("tan((double)fov/2): %f\n", tan((double)fov/2));

    ret.x = coor.x + vec.x * (w_2 / tan((double)fov/2));
    ret.y = coor.y + vec.y * (w_2 / tan((double)fov/2));
    ret.z = coor.z + vec.z * (w_2 / tan((double)fov/2));


    printf("ret.vec: %f, %f, %f\n", ret.x, ret.y, ret.z);
    return (ret);

}

void get_screen_start_position(t_world *world)
{
    t_vec *scr_x;
    t_vec *scr_y;
    t_vec *scr_pos;

    scr_x = &(world->camera.scr_x);
    scr_y = &(world->camera.scr_y);
    scr_pos = &(world->camera.scr_pos);
    *scr_pos = get_screen_origin(*world);
    *scr_x = get_screen_horizon_vec(world->camera.vec);
    *scr_y = get_screen_vertical_vec(world->camera.vec);
    printf("scr_x->vec: %f, %f, %f\n", scr_x->x, scr_x->y, scr_x->z);
    printf("scr_y->vec: %f, %f, %f\n", scr_y->x, scr_y->y, scr_y->z);
    scr_pos->x += (scr_y->x * 250 - scr_x->x * 250);
    scr_pos->y += (scr_y->y * 250 - scr_x->y * 250);
    scr_pos->z += (scr_y->z * 250 - scr_x->z * 250);

    puts("[get_screen_start_position]");
    printf("scr_pos->vec: %f, %f, %f\n", scr_pos->x, scr_pos->y, scr_pos->z);
}
