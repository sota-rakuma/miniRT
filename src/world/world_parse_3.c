#include "../minirt.h"

void	world_parse_ambient_light(t_world *world, char **strs, long row)
{
	const long	len = strs_len(strs);
	t_light		*light;

	if (len != 3)
		ft_printf_and_exit(
			1, "Error\nline %ld: the number of elements: %ld \n", row, len);
	light = (t_light *)ft_xalloc(sizeof(t_light), 1, __func__);
	light->kind = AMBIENT_LIGHT;
	light->intensity = parse_num(strs[1], row);
	if (light->intensity < 0.0 || 1.0 < light->intensity)
		ft_printf_and_exit(
			1, "Error\nline %ld: brightness is out of range\n", row);
	light->color = parse_color(strs[2], row);
	world_add_light(world, light);
}

void	world_parse_light(t_world *world, char **strs, long row)
{
	const long	len = strs_len(strs);
	t_light		*light;

	if (len != 3 && len != 4)
		ft_printf_and_exit(
			1, "Error\nline %ld: the number of elements: %ld \n", row, len);
	light = (t_light *)ft_xalloc(sizeof(t_light), 1, __func__);
	light->kind = LIGHT;
	light->pos = parse_vec3d(strs[1], row);
	light->intensity = parse_num(strs[2], row);
	if (light->intensity < 0.0 || 1.0 < light->intensity)
		ft_printf_and_exit(
			1, "Error\nline %ld: brightness is out of range\n", row);
	if (len == 3)
		light->color = (t_color){255.0, 255.0, 255.0};
	else
		light->color = parse_color(strs[3], row);
	world_add_light(world, light);
}

void	world_parse_camera(t_world *world, char **strs, long row)
{
	const long		len = strs_len(strs);
	double			*tmp;
	t_camera		*camera;

	if (world->camera)
		ft_printf_and_exit(1, "Error\nline %ld: Two or more C's exist\n", row);
	if (len != 4)
		ft_printf_and_exit(
			1, "Error\nline %ld: the number of elements: %ld \n", row, len);
	camera = (t_camera *)ft_xalloc(sizeof(t_camera), 1, __func__);
	world->camera = camera;
	camera->pos = parse_vec3d(strs[1], row);
	camera->normal = parse_vec3d(strs[2], row);
	tmp = (double []){camera->normal.x, camera->normal.y, camera->normal.z};
	if (!check_in_range(tmp, 3, 1.0, -1.0))
		ft_printf_and_exit(1, "Error\nline %ld: normal is out of range\n", row);
	camera->fov = parse_num(strs[3], row);
	if (camera->fov < 0.0 || 180.0 < camera->fov)
		ft_printf_and_exit(1, "Error\nline %ld: fov is out of range\n", row);
}
