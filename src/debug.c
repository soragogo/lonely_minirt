#include "../includes/minirt.h"

void print_ambient(t_fcolor ambient)
{
    puts("[AMBIENT]");
    printf("    Color: (%d, %d, %d)\n", ambient.r, ambient.g, ambient.b);
}

void print_camera(t_dlist camera)
{
    puts("[CAMERA]");
    printf("    座標: (%f, %f, %f)\n", camera.coor.x, camera.coor.y, camera.coor.z);
    printf("    ベクトル: (%f, %f, %f)\n", camera.vec.x, camera.vec.y, camera.vec.z);
    printf("    fov: %d\n", camera.fov);
}

void print_light(t_elem light)
{
    puts("[LIGHT]");
    printf("    obj: %s\n", light.obj);
    printf("    座標: (%f, %f, %f)\n", light.coor.x, light.coor.y, light.coor.z);
    printf("    Color: (%d, %d, %d)\n", light.color.r, light.color.g, light.color.b);
}

void print_objects(t_elem *list)
{
    int i = 0;

    while (list)
    {
        printf("OBJ[%d]: %s\n", i++, list->obj);
        printf("    座標: (%f, %f, %f)\n", list->coor.x, list->coor.y, list->coor.z);
        if (*(list->obj) == 's')
            printf("    Diameter: %f\n", list->diam);
        else if (*(list->obj) == 'p')
            printf("    ベクトル: (%f, %f, %f)\n", list->vec.x, list->vec.y, list->vec.z);
        else
        {
            printf("    ベクトル: (%f, %f, %f)\n", list->vec.x, list->vec.y, list->vec.z);
            printf("    Diameter: %f\n", list->diam);
            printf("    Height: %f\n", list->hgt);
        }
        printf("    Color: (%d, %d, %d)\n", list->color.r, list->color.g, list->color.b);
        list = list->next;
    }
}










void ft_debug(t_world world)
{
    puts("😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀");
    puts("Printing World Struct");
    print_camera(world.camera);
    print_ambient(world.ambient);
    print_light(world.light);
    print_objects(world.objs);
    puts("😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀😀");
}
