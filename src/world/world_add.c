#include "../minirt.h"

void	world_add_light(t_world *world, t_light *light)
{
	light->next = world->light_list;
	world->light_list = light;
}

void	world_add_shape(t_world *world, t_shape *shape)
{
	shape->next = world->shape_list;
	world->shape_list = shape;
}
