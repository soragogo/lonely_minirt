#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <float.h>
#include <../minilibx-linux/mlx.h>

#include "../libft/libft.h"

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;


typedef struct s_fcolor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} t_fcolor;

typedef struct s_dlist
{
    t_vec coor;
    t_vec vec;
    unsigned char fov;
} t_dlist;

typedef struct s_elem
{
    char obj[3];
    t_vec coor;
    t_vec vec;
    t_fcolor color;
    double diam;
    double hgt;
    struct s_elem *next;
} t_elem;

typedef struct s_world {
    void       *mlx;  // minilibx特有のやつ
    void       *win;  // minilibxのウィンドウを指すポインタ
    int        win_w;
    int        win_h;
    t_dlist camera;  // カメラ
    t_elem      *objs;  // 物体のリスト
    t_fcolor    ambient;  // 環境光の強度
    t_elem      light;  // 光源
}               t_world;

typedef struct	s_data {
    void       *mlx;
    void       *win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


/*vector*/
t_vec          vec_init(double x, double y, double z);
t_vec          vec_add(t_vec a, t_vec b);
t_vec          vec_sub(t_vec a, t_vec b);
t_vec          vec_mult(t_vec a, double b);
double         vec_dot(t_vec a, t_vec b);
t_vec          vec_cross(t_vec a, t_vec b);
double         vec_mag(t_vec a);
t_vec          vec_normalize(t_vec a);
void            get_vec_from_str(t_vec *vec, char *str, int is_vector);

/*error_handling*/
void ft_error(char *log);
void check_color_syntax(char *str);
void check_vec_syntax(char *str);
void check_comma_syntax(char *str);

/*add_elements_utils*/
double atod(char *str);
void get_color_from_str(t_fcolor *color, char *str);

/*free utils*/
void clean_world(t_world *world);
void free_matrix(char **matrix);

/*atod*/
double atod(char *str);

/*init_world*/
void init_world(t_world *world);

/*read_map*/
int open_scene(const char *file);
void add_elements(t_world *world, int fd);
void add_element(t_world *world, char *line, int *a_c_l);

/*add_camera*/
void add_camera(t_world *world, char *line, int count);
/*add_light*/
void add_light(t_world *world, char *line, int count);

/*add_ambient*/
void add_ambient(t_world *world, char *line, int count);

/*add_objects*/
void add_object(t_world *world, char *line);
void create_obj_list(t_world *world, char **matrix);
void create_new_obj(t_elem *new_obj, char **matrix);
t_elem *find_last_obj(t_world *world);

/*init minilibx*/
void init_minilibx(t_world *world, t_data *img);

/*event_hook*/
void event_hook(t_data *img);


/*debug*/
void ft_debug(t_world world);

#endif
