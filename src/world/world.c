#include "../minirt.h"

// ワールド情報は現状直接書いてる
// TODO: パースした情報を入れる
t_world	*world_init(char *filename) {
	t_world *world;

	world = malloc(sizeof(t_world));
	world->shape_list = NULL;
	world->light_list = NULL;

	world->bg = (t_color){30.0, 30.0, 30.0};

	world_parse(world, filename);

	return world;
}
