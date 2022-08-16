#include "../minirt.h"

t_shape	*compute_intersected_shape(t_world *world, t_vec3d to_screen)
{
	t_vec3d	camera_to_screen;
	t_shape	*now_shape;
	t_shape	*intersected_shape;
	double	minimum_t;
	double	t;

	camera_to_screen = vec3d_camera_to_screen(world->camera, to_screen);
	intersected_shape = NULL;
	minimum_t = -1;
	now_shape = world->shape_list;
	while (now_shape)
	{
		t = shape_get_intersection(
				camera_to_screen, vec3d_camera(world->camera), now_shape);
		if (t >= 1.0 && (intersected_shape == NULL || minimum_t > t))
		{
			intersected_shape = now_shape;
			minimum_t = t;
		}
		now_shape = now_shape->next;
	}
	return (intersected_shape);
}

t_color	compute_ambient_light(t_shape *shape, t_light *light)
{
	t_color	ia;
	t_color	radience_amb;

	ia = color_mult_num(light->color, light->intensity / 255.0);
	radience_amb = color_mult_color(ia, shape->ka);
	return (radience_amb);
}

t_vec3d	compute_intersected_pos(
	t_camera *camera, t_vec3d to_screen, t_shape *shape)
{
	t_vec3d	o_to_screen;
	double	t;
	t_vec3d	pos;

	o_to_screen = vec3d_camera_to_screen(camera, to_screen);
	t = shape_get_intersection(o_to_screen, camera->pos, shape);
	pos = vec3d_add(camera->pos, vec3d_mult(o_to_screen, t));
	return (pos);
}

bool	compute_is_shadow(t_world *world, t_light *light,
					t_vec3d intersected_pos)
{
	t_shape	*now_shape;
	t_vec3d	int_to_light_dir;
	double	t;

	now_shape = world->shape_list;
	int_to_light_dir = vec3d_sub(light->pos, intersected_pos);
	while (now_shape)
	{
		t = shape_get_intersection(
				int_to_light_dir,
				vec3d_add(intersected_pos,
					vec3d_mult(int_to_light_dir,
						0.000000001 / vec3d_length(int_to_light_dir))),
				now_shape);
		if (0.0 < t && t < 1.0)
			return (true);
		now_shape = now_shape->next;
	}
	return (false);
}

void	set_t_compute(t_world *world, t_vec3d to_screen, t_compute *c)
{
	c->o_to_screen = vec3d_camera_to_screen(world->camera, to_screen);
	c->pos_to_light_dir = vec3d_sub(c->light->pos, c->intersected_pos);
	if (vec3d_length(c->pos_to_light_dir) == 0)
		c->pos_to_light_dir = (t_vec3d){0, 0, 0};
	else
		c->pos_to_light_dir = vec3d_unit(c->pos_to_light_dir);
	c->intersected_pos_normal = shape_normal_vec(c->shape, c->intersected_pos);
	c->reverse_eye_dir = vec3d_unit(vec3d_mult(c->o_to_screen, -1.0));
	if (vec3d_dot(c->reverse_eye_dir, c->intersected_pos_normal) <= 0.0)
		c->intersected_pos_normal = vec3d_mult(c->intersected_pos_normal, -1.0);
	c->cosA = double_max(
			0.0, vec3d_dot(c->pos_to_light_dir, c->intersected_pos_normal));
	c->light_color = color_mult_num(
			c->light->color, c->light->intensity / 255.0);
}
