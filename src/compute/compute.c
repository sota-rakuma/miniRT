#include "../minirt.h"

t_shape	*compute_intersected_shape(t_world *world, t_vec3d to_screen);
t_color	compute_ambient_light(t_shape *shape, t_light *light);
t_vec3d	compute_intersected_pos(
			t_camera *camera, t_vec3d to_screen, t_shape *shape);
bool	compute_is_shadow(t_world *world, t_light *light,
			t_vec3d intersected_pos);
void	set_t_compute(t_world *world, t_vec3d to_screen, t_compute *c);

t_color	compute_specular(t_compute *c)
{
	t_color	radience_spe;
	t_vec3d	r;

	radience_spe = (t_color){0, 0, 0};
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
	if (compute_is_shadow(world, light, c.intersected_pos))
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
			add_intensity = compute_ambient_light(shape, now_light);
		if (now_light->kind == LIGHT)
			add_intensity = compute_light(world, to_screen, shape, now_light);
		intensity = color_add_color(intensity, add_intensity);
		now_light = now_light->next;
	}
	return (intensity);
}

t_color	compute_color_of_pixel(t_world *world, t_vec3d to_screen)
{
	t_shape	*intersected_shape;
	t_color	color;

	intersected_shape = compute_intersected_shape(world, to_screen);
	if (intersected_shape == NULL)
		return (world->bg);
	color = compute_brightness(world, to_screen, intersected_shape);
	color = color_normalize(color);
	color = color_mult_num(color, 255.0);
	return (color);
}
