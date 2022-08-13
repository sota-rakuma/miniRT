#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 600
# define HEIGHT 600

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <mlx.h>
# include "../libft/libft.h"

# include "vec3d/vec3d.h"
# include "color/color.h"
# include "world/world.h"
# include "compute/compute.h"
# include "display/display.h"
# include "util/util.h"

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

typedef struct s_all_info
{
	t_world		*world;
	t_display	*display;
}	t_all_info;

int	key_event(int key_code, void *param);
int	click_cross_event(void *param);

#endif /* MINIRT_H */
