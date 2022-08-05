#ifndef WORLD_H
#define WORLD_H

// world_add.c
void	world_add_light(t_world *world, t_light *light);
void	world_add_shape(t_world *world, t_shape *shape);

// world_parse.c
void	world_parse(t_world *world, char *filename, int fd);

t_world	*world_init();

#endif
