#ifndef SHAPE_H
#define SHAPE_H

#include "../minirt.h"

double with_sphere(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double with_plane(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double with_cylinder(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double shape_get_intersection(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);

#endif /* SHAPE_H */
