#include "../minirt.h"

static t_vec3d vec3d_camera(t_camera *camera) {
    return (camera->pos);
}

double with_sphere(t_vec3d o_to_screen, t_camera *camera, t_shape *shape)
{
    t_vec3d center_to_o = vec3d_sub(vec3d_camera(camera),
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

double with_plane(t_vec3d o_to_screen, t_camera *camera, t_shape *shape)
{
    t_vec3d o_to_point = vec3d_sub(shape->point, vec3d_camera(camera));
    double a = vec3d_dot(shape->oriental_normal, o_to_screen);
    double  b = vec3d_dot(shape->oriental_normal, o_to_point);
	if (a != 0.0)
		return (b / a);
	return (-1.0);
}
