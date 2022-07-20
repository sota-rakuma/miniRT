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

// ワールド情報は現状直接書いてる
// TODO: パースした情報を入れる
t_world	*world_init() {
	t_world *world;

	world = malloc(sizeof(t_world));
	world->shape_list = NULL;
	world->light_list = NULL;

	world->bg = (t_color){0.0, 0.0, 255.0};
	world->camera = (t_camera){(t_vec3d){0, 0, -5}, 0.0};

	{
		t_shape *shape = malloc(sizeof(t_shape));
		shape->kind = SPHERE;
		shape->center = (t_vec3d){0, 0, 5};
		shape->radius = 1.0;
		shape->color = (t_color){255.0, 255.0, 255.0};
		world_add_shape(world, shape);
	}

	{
		t_light *light = malloc(sizeof(t_light));
		light->kind = AMBIENT_LIGHT;
		// light->intensity =
		world_add_light(world, light);
	}

	{
		t_light *light = malloc(sizeof(t_light));
		light->kind = LIGHT;
		light->pos = (t_vec3d){-5.0, 5.0, -5.0};
		world_add_light(world, light);
	}
	return world;
}
