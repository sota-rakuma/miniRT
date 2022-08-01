#include "../minirt.h"

// ワールド情報は現状直接書いてる
// TODO: パースした情報を入れる
t_world	*world_init(char *filename) {
	const t_color bg =(t_color){30.0, 30.0, 30.0};
	t_world *world;

	world = ft_calloc(1, sizeof(t_world));
	world->bg = bg;
	world_parse(world, filename);
	return world;
}
