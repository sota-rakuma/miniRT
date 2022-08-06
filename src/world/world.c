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
		ft_printf_and_exit(1, "FILE %s: camera is not found\nError\n", file);
	else if (world->a_cnt != 1)
		ft_printf_and_exit(
			1, "FILE %s: wrong number of ambient light\nError\n", file);
	else if (BONUS_FLAG && world->l_cnt != 1)
		ft_printf_and_exit(1, "FILE %s: wrong number of light\nError\n", file);
}

// ワールド情報は現状直接書いてる
// TODO: パースした情報を入れる
t_world	*world_init(char *filename)
{
	const t_color	bg = (t_color){30.0, 30.0, 30.0};
	t_world			*world;
	int				fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("cannot open file");
		exit(1);
	}
	world = ft_calloc(1, sizeof(t_world));
	if (!world)
	{
		printf("in %s, failed to malloc\n", __func__);
		close(fd);
		exit(1);
	}
	world->bg = bg;
	world_parse(world, fd);
	world_check(world, filename);
	close(fd);
	return (world);
}
