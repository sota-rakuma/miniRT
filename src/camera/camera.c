#include "../minirt.h"

static void	camera_set_base_vec(t_camera *camera)
{
	t_vec3d	a;

	if (camera->normal.x < -0.9 || 0.9 < camera->normal.x)
		a = (t_vec3d){0, 1, 0};
	else
		a = (t_vec3d){1, 0, 0};
	camera->screen_vertical_normal = vec3d_cross(a, camera->normal);
	camera->screen_vertical_normal = vec3d_unit(
			camera->screen_vertical_normal);
	camera->screen_horizon_normal = vec3d_cross(
			camera->normal,
			camera->screen_vertical_normal);
}

static void	camera_set_start_pos(t_camera *camera)
{
	const double	d = 1.0;
	double			horizon_d;
	double			vertical_d;
	t_vec3d			screen_center_pos;
	t_vec3d			screen_left_pos;

	screen_center_pos = vec3d_add(camera->pos, vec3d_mult(camera->normal, d));
	if (camera->fov == 0.0)
	{
		camera->screen_start_pos = screen_center_pos;
		camera->screen_horizon_normal = (t_vec3d){0, 0, 0};
		camera->screen_vertical_normal = (t_vec3d){0, 0, 0};
		return ;
	}
	horizon_d = d * tan(camera->fov / 2.0);
	vertical_d = horizon_d * (double)HEIGHT / (double)WIDTH;
	camera->screen_height = 2.0 * vertical_d;
	camera->screen_width = 2.0 * horizon_d;
	screen_left_pos = vec3d_add(
			screen_center_pos,
			vec3d_mult(camera->screen_horizon_normal, -1.0 * horizon_d));
	camera->screen_start_pos = vec3d_add(
			screen_left_pos,
			vec3d_mult(camera->screen_vertical_normal, -1.0 * vertical_d));
}

void	camera_set(t_camera *camera)
{
	camera->normal = vec3d_unit(camera->normal);
	camera->fov = M_PI * camera->fov / 180.0;
	camera_set_base_vec(camera);
	camera_set_start_pos(camera);
	camera->dx = camera->screen_width / (double)WIDTH;
	camera->dy = camera->screen_height / (double)HEIGHT;
}
