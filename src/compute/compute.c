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

t_color	compute_ambient_light(t_world *world, t_shape *shape, t_light *light)
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

bool	compute_is_shadow(t_world *world, t_shape *shape, t_light *light,
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
	c->pos_to_light_dir = \
		vec3d_unit(vec3d_sub(c->light->pos, c->intersected_pos));
	c->intersected_pos_normal = shape_normal_vec(c->shape, c->intersected_pos);
	c->reverse_eye_dir = vec3d_unit(vec3d_mult(c->o_to_screen, -1.0));
	if (vec3d_dot(c->reverse_eye_dir, c->intersected_pos_normal) <= 0.0)
		c->intersected_pos_normal = vec3d_mult(c->intersected_pos_normal, -1.0);
	c->cosA = double_max(
			0.0, vec3d_dot(c->pos_to_light_dir, c->intersected_pos_normal));
	c->light_color = color_mult_num(
			c->light->color, c->light->intensity / 255.0);
}

t_color	compute_specular(t_compute *c)
{
	t_color	radience_spe;
	t_vec3d	r;

	if (c->cosA > 0)
	{
		r = vec3d_sub(
				vec3d_mult(c->intersected_pos_normal,
					2 * (c->cosA)), c->pos_to_light_dir);
		radience_spe = color_mult_num(
				color_mult_color(c->shape->ks, c->light_color),
				pow(double_max(vec3d_dot(c->reverse_eye_dir, r), 0.0),
					c->shape->shininess));
	}
	return (radience_spe);
}

t_color	compute_diffuse(t_compute *c)
{
	t_color	radience_dif;

	radience_dif = \
		color_mult_num(color_mult_color(c->shape->kd, c->light_color), c->cosA);
	return (radience_dif);
}

t_color	compute_light(
	t_world *world, t_vec3d to_screen, t_shape *shape, t_light *light)
{
	t_color		color;
	t_compute	c;

	color = (t_color){0.0, 0.0, 0.0};
	c.shape = shape;
	c.light = light;
	c.intersected_pos = \
			compute_intersected_pos(world->camera, to_screen, shape);
	if (compute_is_shadow(world, shape, light, c.intersected_pos))
		return ((t_color){0.0, 0.0, 0.0});
	set_t_compute(world, to_screen, &c);
	color = color_add_color(color, compute_diffuse(&c));
	color = color_add_color(color, compute_specular(&c));
	return (color);
}

t_color	compute_brightness(t_world *world, t_vec3d to_screen, t_shape *shape)
{
	t_color	intensity;
	t_color	add_intensity;
	t_light	*now_light;

	if (shape == NULL)
		return ((t_color){0.0, 0.0, 0.0});
	intensity = (t_color){0.0, 0.0, 0.0};
	now_light = world->light_list;
	while (now_light)
	{
		if (now_light->kind == AMBIENT_LIGHT)
			add_intensity = compute_ambient_light(world, shape, now_light);
		if (now_light->kind == LIGHT)
			add_intensity = compute_light(world, to_screen, shape, now_light);
		intensity = color_add_color(intensity, add_intensity);
		now_light = now_light->next;
	}
	return (intensity);
}

t_color	compute_color_of_pixel(t_world *world, t_vec3d to_screen)
{
	t_vec3d	o_to_screen;
	t_shape	*intersected_shape;
	t_color	color;

	o_to_screen = vec3d_camera_to_screen(world->camera, to_screen);
	intersected_shape = compute_intersected_shape(world, to_screen);
	if (intersected_shape == NULL)
		return (world->bg);
	color = compute_brightness(world, to_screen, intersected_shape);
	color = color_normalize(color);
	color = color_mult_num(color, 255.0);
	return (color);
}
