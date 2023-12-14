#include "../includes/minirt.h"
t_vec          vec_init(double x, double y, double z)
{
    t_vec new_vec;

    new_vec.x = x;
    new_vec.y = y;
    new_vec.z = z;

    return (new_vec);
}

t_vec          vec_add(t_vec a, t_vec b)
{
    t_vec new_vec;

    new_vec.x = a.x + b.x;
    new_vec.y = a.y + b.y;
    new_vec.z = a.z + b.z;

    return (new_vec);

}

t_vec          vec_sub(t_vec a, t_vec b)
{
    t_vec new_vec;

    new_vec.x = a.x - b.x;
    new_vec.y = a.y - b.y;
    new_vec.z = a.z - b.z;

    return (new_vec);
}

t_vec          vec_mult(t_vec a, double b)
{
    t_vec new_vec;

    new_vec.x = a.x * b;
    new_vec.y = a.y * b;
    new_vec.z = a.z * b;

    return (new_vec);
}

double         vec_dot(t_vec a, t_vec b)
{
    double dot;

    dot = (a.x * b.x)
        + (a.y * b.y)
        + (a.z * b.z);

    return (dot);
}

t_vec          vec_cross(t_vec a, t_vec b)
{
    t_vec new_vec;

    new_vec.x = a.y * b.z - a.z - b.y;
    new_vec.y = a.z * b.x - a.x - b.z;
    new_vec.z = a.x * b.y - a.y - b.x;

    return (new_vec);
}

double         vec_mag(t_vec a)
{
    double mag;

    mag = pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2);
    mag = sqrt(mag);
    return (mag);
}

double          vec_sum(t_vec a)
{
    double sum;
    sum = a.x + a.y + a.z;

    return sum;
}

t_vec          vec_normalize(t_vec a)
{
    double mag;
    t_vec normal_a;
    mag = vec_mag(a);
    if (mag == 0)
        return (a);
    normal_a.x = a.x / mag;
    normal_a.y = a.y / mag;
    normal_a.z = a.z / mag;
    return (normal_a);
}
