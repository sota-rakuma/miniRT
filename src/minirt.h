#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 200
# define HEIGHT 200

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <mlx.h>
# include "../libft/libft.h"

# include "vec3d/vec3d.h"
# include "color/color.h"

# include "world/world.h"
# include "compute/compute.h"
# include "display/display.h"

enum e_x11_events {
	X11_ON_DESTROY = 17,
};

enum e_x11_masks {
	X11_STRUCTURE_NOTIFY_MASK = (1L << 17),
};

typedef struct s_compute {
	t_shape	*shape;
	t_light	*light;
	t_vec3d	o_to_screen;
	t_vec3d	intersected_pos;
	t_vec3d	pos_to_light_dir;
	t_vec3d	intersected_pos_normal;
	t_vec3d	reverse_eye_dir;
	double	cosA;
	t_color	light_color;
}	t_compute;

#endif /* MINIRT_H */
