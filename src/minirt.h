#ifndef MINIRT_H
#define MINIRT_H

#define WIDTH 200
#define HEIGHT 200

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>
#include "../libft/libft.h"

#include "vec3d/vec3d.h"
#include "color/color.h"

typedef struct s_sphere {
	t_vec3d center;
	double radius;
	t_color color;
} t_sphere;

#include "world/world.h"

typedef struct s_compute {
	t_shape *shape;
	t_light *light;
	t_vec3d o_to_screen;
	t_vec3d intersected_pos;
	t_vec3d pos_to_light_dir;
	t_vec3d intersected_pos_normal;
	t_vec3d reverse_eye_dir;
	double cosA;
	t_color light_color;
} t_compute;

#include "display/display.h"

t_color compute_mirror(t_world *world, t_shape *shape, t_vec3d o_to_screen, double t, long count, t_vec3d pos);

#endif /* MINIRT_H */
