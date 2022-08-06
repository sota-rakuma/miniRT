#include "../minirt.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#ifdef BONUS
# define BONUS_FLAG 1
#else
# define BONUS_FLAG 0
#endif

void	world_destuctor(t_world *world)
{
	t_light	*light;
	t_shape	*shape;

	light = world->light_list;
	while (light)
	{
		world->light_list = light->next;
		free(light);
		light = world->light_list;
	}
	shape = world->shape_list;
	while (shape)
	{
		world->shape_list = shape->next;
		free(shape);
		shape = world->shape_list;
	}
	free(world->camera);
	free(world);
}

void	world_check(t_world *world, const char *file)
{
	t_light	*light;

	light = world->light_list;
	while (light)
	{
		if (light->kind == AMBIENT_LIGHT)
			world->a_cnt++;
		else
			world->l_cnt++;
		light = light->next;
	}
	if (!world->camera)
		ft_printf_and_exit(1, "Error\nFILE %s: camera is not found\n", file);
	else if (world->a_cnt != 1)
		ft_printf_and_exit(
			1, "Error\nFILE %s: wrong number of ambient light\n", file);
	else if (BONUS_FLAG == 0 && world->l_cnt != 1)
		ft_printf_and_exit(1, "Error\nFILE %s: wrong number of light\n", file);
}

// ワールド情報は現状直接書いてる
// TODO: パースした情報を入れる
t_world	*world_init(char *filename)
{
	const t_color	bg = (t_color){30.0, 30.0, 30.0};
	t_world			*world;
	int				fd;

	if (!check_filename(filename))
		ft_printf_and_exit(1, "Error\nFILE %s: Not .rt extension\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\ncannot open file");
		exit(1);
	}
	world = ft_calloc(1, sizeof(t_world));
	if (!world)
	{
		printf("Error\nin %s, failed to malloc\n", __func__);
		close(fd);
		exit(1);
	}
	world->bg = bg;
	world_parse(world, fd);
	world_check(world, filename);
	close(fd);
	return (world);
}
