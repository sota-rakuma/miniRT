#include "../minirt.h"

double	shape_get_intersection(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
	if (shape->kind == SPHERE)
		return (with_sphere(o_to_screen, o, shape));
	if (shape->kind == PLANE)
		return (with_plane(o_to_screen, o, shape));
	if (shape->kind == CYLINDER)
		return (with_cylinder(o_to_screen, o, shape));
	return (0.0);
}
