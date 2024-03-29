#ifndef WORLD_H
# define WORLD_H

# include "../../libft/libft.h"
# include <sys/errno.h>
# include <stdio.h>
# include "../light/light.h"
# include "../shape/shape.h"
# include "../camera/camera.h"

typedef struct s_world {
	t_light		*light_list;
	long		a_cnt;
	long		l_cnt;
	t_shape		*shape_list;
	t_camera	*camera;
	t_color		bg;
}				t_world;

typedef enum e_check
{
	INTEGER,
	FLOAT
}	t_check;

// world_add.c
void	world_add_light(t_world *world, t_light *light);
void	world_add_shape(t_world *world, t_shape *shape);

bool	check_in_range(double val[], size_t len, double max, double min);
bool	check_comma_cnt(char *str);
bool	check_elements(char **strs, t_check kind);
bool	check_filename(char *filename);

double	parse_num(char *str, long row);
double	parse_positive_num(char *str, long row);
t_vec3d	parse_vec3d(char *str, long row);
t_color	parse_color(char *str, long row);
void	world_parse_ambient_light(t_world *world, char **strs, long row);
void	world_parse_light(t_world *world, char **strs, long row);
void	world_parse_camera(t_world *world, char **strs, long row);
void	world_parse_sphere(t_world *world, char **strs, long row);
void	world_parse_plane(t_world *world, char **strs, long row);
void	world_parse_cylinder(t_world *world, char **strs, long row);

// world_parse.c
void	world_destuctor(t_world *world);
void	world_parse(t_world *world, int fd);
void	world_check(t_world *world);

t_world	*world_init(char *filename);

#endif
