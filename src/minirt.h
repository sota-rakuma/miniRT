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
#include "camera/camera.h"

typedef struct s_sphere {
	t_vec3d center;
	double radius;
	t_color color;
} t_sphere;

// light
typedef enum e_light_kind{
	AMBIENT_LIGHT,
	LIGHT,
} t_light_kind;

typedef struct s_light {
	struct s_light	*next;
	t_light_kind	kind;

	// common
	double  intensity;

	// ambient_light
	t_color	color;

	// light
	t_vec3d			pos;
} t_light;

// shape
typedef enum e_shape_kind {
	SPHERE,
	PLANE,
	CYLINDER,
} t_shape_kind;

typedef struct s_shape {
	struct s_shape	*next;
	t_shape_kind	kind;

	// common
	t_color			color;
	t_color			ka;
	t_color			kd;
	t_color			ks;
	double			shininess;

	// sphere
	t_vec3d			center;
	double			radius;

	// plane
	t_vec3d			normal;
	t_vec3d			point;
	bool			is_mirror;

	// cylinder
	// t_vec3d			center;
	// t_vec3d			normal;
	// double			radius;
	double				height;
} t_shape;

typedef struct s_world {
	t_light		*light_list;
	t_shape		*shape_list;
	t_camera	*camera;
	t_color		bg;
} t_world;


#include "display/display.h"
#include "util/util.h"
#include "shape/shape.h"
#include "world/world.h"

t_color compute_mirror(t_world *world, t_shape *shape, t_vec3d o_to_screen, double t, long count, t_vec3d pos);

#endif /* MINIRT_H */
