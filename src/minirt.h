#ifndef MINIRT_H
#define MINIRT_H

#define WIDTH 600
#define HEIGHT 600

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>

#include "vec3d/vec3d.h"
#include "color/color.h"

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
} t_shape_kind;

typedef struct s_shape {
	struct s_shape	*next;
	t_shape_kind	kind;

	// common
	t_color			color;

	// sphere
	t_vec3d			center;
	double			radius;
} t_shape;

// camera
typedef struct s_camera {
	t_vec3d	pos;
	double	fov;
} t_camera;

typedef struct s_world {
	t_light		*light_list;
	t_shape		*shape_list;
	t_camera	camera;
	t_color		bg;
} t_world;

#include "screen/screen.h"
#include "util/util.h"
#include "world/world.h"

#endif
