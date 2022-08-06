#include "../minirt.h"

void	world_parse_sphere(t_world *world, char **strs, long row)
{
	long	len;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 4)
		ft_printf_and_exit(
			1, "line %ld: number of elements: %ld \nError\n", row, len);
	shape = (t_shape *)ft_xalloc(sizeof(t_shape), 1, __func__);
	shape->kind = SPHERE;
	shape->center = parse_vec3d(strs[1], row);
	shape->radius = parse_num(strs[2], row) / 2.0;
	shape->color = parse_color(strs[3], row);
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	world_add_shape(world, shape);
}

void	world_parse_plane(t_world *world, char **strs, long row)
{
	long	len;
	double	*tmp;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 4 && (len != 5 || ft_strcmp(strs[4], "mirror")))
		ft_printf_and_exit(
			1, "line %ld: the number of elements: %ld \nError\n", row, len);
	shape = (t_shape *)ft_xalloc(sizeof(t_shape), 1, __func__);
	shape->kind = PLANE;
	shape->point = parse_vec3d(strs[1], row);
	shape->normal = parse_vec3d(strs[2], row);
	tmp = (double []){shape->normal.x, shape->normal.y, shape->normal.z};
	if (!check_in_range(tmp, 3, 1.0, -1.0))
		ft_printf_and_exit(1, "line %ld: normal is out of range\nError\n", row);
	shape->color = parse_color(strs[3], row);
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	if (len == 5)
		shape->is_mirror = true;
	world_add_shape(world, shape);
}

void	world_parse_cylinder(t_world *world, char **strs, long row)
{
	long	len;
	double	*tmp;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 6)
		ft_printf_and_exit(
			1, "line %ld: the number of elements: %ld \nError\n", row, len);
	shape = (t_shape *)ft_xalloc(sizeof(t_shape), 1, __func__);
	shape->kind = CYLINDER;
	shape->normal = parse_vec3d(strs[2], row);
	tmp = (double []){shape->normal.x, shape->normal.y, shape->normal.z};
	if (!check_in_range(tmp, 3, 1.0, -1.0))
		ft_printf_and_exit(1, "line %ld: normal is out of range\nError\n", row);
	shape->normal = vec3d_unit(shape->normal);
	shape->radius = parse_num(strs[3], row) / 2.0;
	shape->height = parse_num(strs[4], row);
	shape->color = parse_color(strs[5], row);
	shape->center = parse_vec3d(strs[1], row);
	shape->center = vec3d_add(
			shape->center, vec3d_mult(shape->normal, shape->height / 2.0));
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	world_add_shape(world, shape);
}
