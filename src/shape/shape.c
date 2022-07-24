#include "../minirt.h"

static t_vec3d vec3d_camera(t_camera *camera) {
    return (camera->pos);
}

double with_sphere(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
    t_vec3d center_to_o = vec3d_sub(o,
                                    shape->center);
    // 判別式
    double a = vec3d_dot(o_to_screen, o_to_screen);
    double b = 2 * vec3d_dot(o_to_screen, center_to_o);
    double c =
        vec3d_dot(center_to_o, center_to_o) - shape->radius * shape->radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant == 0)
        return (-b / (2 * a));
    else if (discriminant > 0) {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        double t_min = t1 > t2 ? t2 : t1;
        double t_max = t1 > t2 ? t1 : t2;
		return (t1 > 0 && t2 > 0 ? t_min : t_max);
    }
	return (-1.0);
}

double with_plane(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
    t_vec3d o_to_point = vec3d_sub(shape->point, o);
    double a = vec3d_dot(shape->oriental_normal, o_to_screen);
    double  b = vec3d_dot(shape->oriental_normal, o_to_point);
	if (a != 0.0)
		return (b / a);
	return (-1.0);
}

double with_cylinder(t_vec3d o_to_screen, t_vec3d o, t_shape *shape)
{
    // P = O + tD
    // CP = P - C = O + tD - C

    // |CP x v| = radius
    // |(O + tD - C) x v| = radius
    // |(O x v) + t(D x v) - (C x v)|^2 = radius^2
    // a = (D x v)^2
    // b = 2 * (D x v)dot((O x v) - (C x v))
    //   = 2 ((D x v)dot(O x v) - (D x v)dot(C x v)) 
    // c = (O x v)^2 - 2 * (O x v)dot(C x v) + (C x v)^2 - radius^2

    t_vec3d v = vec3d_mult(shape->oriental_normal, 1.0 / vec3d_length(shape->oriental_normal));
    t_vec3d d_cross_v = vec3d_cross(o_to_screen, v);
    t_vec3d o_cross_v = vec3d_cross(o, v);
    t_vec3d c_cross_v = vec3d_cross(shape->center, v);
    
    double a = vec3d_dot(d_cross_v, d_cross_v);
    double b = 2.0 * (vec3d_dot(d_cross_v, o_cross_v) - vec3d_dot(d_cross_v, c_cross_v));
    double c = vec3d_dot(o_cross_v, o_cross_v) - 2.0 * vec3d_dot(o_cross_v, c_cross_v) + vec3d_dot(c_cross_v, c_cross_v) - shape->radius * shape->radius;
    
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0)
        return (-1);
    if (discriminant == 0)
        return (b / a);        
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    double t_min = t1 > t2 ? t2 : t1;
    double t_max = t1 > t2 ? t1 : t2;
    
	return (t1 > 0 && t2 > 0 ? t_min : t_max);
}
