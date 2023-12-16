#include "../includes/minirt.h"

void print_ambient(double *ambient)
{
    puts("[AMBIENT]");
    printf("    Color: (%f, %f, %f)\n", ambient[0], ambient[1], ambient[2]);
}

void print_camera(t_dlist camera)
{
    puts("[CAMERA]");
    printf("    座標: (%f, %f, %f)\n", camera.coor.x, camera.coor.y, camera.coor.z);
    printf("    ベクトル: (%f, %f, %f)\n", camera.vec.x, camera.vec.y, camera.vec.z);
    printf("    fov: %d\n", camera.fov);
}

void print_light(t_light light)
{
    puts("[LIGHT]");
    printf("    座標: (%f, %f, %f)\n", light.coor.x, light.coor.y, light.coor.z);
    printf("    Color: (%f, %f, %f)\n", light.rgb[0], light.rgb[1], light.rgb[2]);
}

void print_objects(t_elem *list)
{
    int i = 0;

    while (list)
    {
        printf("OBJ[%d]: %s\n", i++, list->obj);
        printf("    座標: (%f, %f, %f)\n", list->coor.x, list->coor.y, list->coor.z);
        if (*(list->obj) == 's')
            printf("    Radius: %f\n", list->radius);
        else if (*(list->obj) == 'p')
            printf("    ベクトル: (%f, %f, %f)\n", list->vec.x, list->vec.y, list->vec.z);
        else
        {
            printf("    ベクトル: (%f, %f, %f)\n", list->vec.x, list->vec.y, list->vec.z);
            printf("    Radius: %f\n", list->radius);
            printf("    Height: %f\n", list->hgt);
        }
        printf("    Color: (%d, %d, %d)\n", list->color.r, list->color.g, list->color.b);
        list = list->next;
    }
}










void ft_debug(t_world world)
{
    puts("😀😀😀😀😀😀😀😀😀😀DEBUG😀😀😀😀😀😀😀😀😀😀");
    puts("Printing World Struct");
    print_camera(world.camera);
    print_ambient(world.ambient);
    print_light(world.light);
    print_objects(world.objs);
    puts("😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀");
}
