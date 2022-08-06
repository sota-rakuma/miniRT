#include "../minirt.h"

typedef struct s_abc {
    double a;
    double b;
    double c;
} t_abc;

double with_sphere(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
    double t1;
    double t2;
    const t_vec3d center_to_o = vec3d_sub(o, shape->center);
    const t_abc eq = (t_abc){
        vec3d_dot(o_to_screen, o_to_screen),
        2 * vec3d_dot(o_to_screen, center_to_o),
        vec3d_dot(center_to_o, center_to_o) - shape->radius * shape->radius
    };
    const double discriminant = eq.b * eq.b - 4 * eq.a * eq.c;

    if (discriminant == 0)
        return (-eq.b / (2 * eq.a));
    t1 = (-eq.b - sqrt(discriminant)) / (2 * eq.a);
    t2 = (-eq.b + sqrt(discriminant)) / (2 * eq.a);
    if (t1 > 0 && t2 > 0)
        return double_min(t1, t2);
    return double_max(t1, t2);
}

double with_plane(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
    t_vec3d o_to_point = vec3d_sub(shape->point, o);
    double a = vec3d_dot(shape->normal, o_to_screen);
    double  b = vec3d_dot(shape->normal, o_to_point);
	if (a != 0.0)
		return (b / a);
	return (-1.0);
}

t_abc   equation_cylinder(t_vec3d o_to_screen, t_vec3d o, t_shape *shape){
    t_vec3d d_cross_v = vec3d_cross(o_to_screen, shape->normal);
    t_vec3d o_cross_v = vec3d_cross(o, shape->normal);
    t_vec3d c_cross_v = vec3d_cross(shape->center, shape->normal);
    double max_length = sqrt(pow(shape->height / 2, 2) + pow(shape->radius, 2));
    double a = vec3d_dot(d_cross_v, d_cross_v);
    double b = 2.0 * (vec3d_dot(d_cross_v, o_cross_v) - vec3d_dot(d_cross_v, c_cross_v));
    double c = vec3d_dot(o_cross_v, o_cross_v) - 2.0 * vec3d_dot(o_cross_v, c_cross_v) + vec3d_dot(c_cross_v, c_cross_v) - shape->radius * shape->radius;
    return (t_abc){a, b, c};
}

double get_t_with_cylinder(t_vec3d o_to_screen, t_vec3d o, t_shape *shape, t_abc abc) {
    const double max_length = sqrt(
        pow(shape->height / 2, 2) + pow(shape->radius, 2));
    const double discriminant = abc.b * abc.b - 4.0 * abc.a * abc.c;
    t_vec3d c_to_point;
    double t1 = (-abc.b - sqrt(discriminant)) / (2 * abc.a);
    c_to_point = vec3d_sub(vec3d_add(o, vec3d_mult(o_to_screen, t1)), shape->center);
    if (vec3d_length(c_to_point) > max_length)
        t1 = -1;
    double t2 = (-abc.b + sqrt(discriminant)) / (2 * abc.a);
    c_to_point = vec3d_sub(vec3d_add(o, vec3d_mult(o_to_screen, t2)), shape->center);
    if (vec3d_length(c_to_point) > max_length)
        t2 = -1;
    if (t1 > 0 && t2 > 0)
        return double_min(t1, t2);
    return double_max(t1, t2);
}

// P = O + tD
// CP = P - C = O + tD - C
//
// |CP x v| = radius
// |(O + tD - C) x v| = radius
// |(O x v) + t(D x v) - (C x v)|^2 = radius^2
// a = (D x v)^2
// b = 2 * (D x v)dot((O x v) - (C x v))
//   = 2 ((D x v)dot(O x v) - (D x v)dot(C x v))
// c = (O x v)^2 - 2 * (O x v)dot(C x v) + (C x v)^2 - radius^2
double with_cylinder(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
    t_abc abc = equation_cylinder(o_to_screen, o, shape);
    double discriminant = abc.b * abc.b - 4.0 * abc.a * abc.c;
    if (discriminant < 0.0)
        return (-1);
    else
        return get_t_with_cylinder(o_to_screen, o, shape, abc);
}

double shape_get_intersection(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
    if (shape->kind == SPHERE)
        return with_sphere(o_to_screen, o, shape);
    if (shape->kind == PLANE)
        return with_plane(o_to_screen, o, shape);
    if (shape->kind == CYLINDER)
        return with_cylinder(o_to_screen, o, shape);
    return (0.0);
}
