#include "../minirt.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

// ワールド情報は現状直接書いてる
// TODO: パースした情報を入れる
t_world	*world_init(char *filename)
{
	const t_color	bg =(t_color){30.0, 30.0, 30.0};
	t_world			*world;
	char			*line;
	int				fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("cannot open file");
		//printf("cannot open file\n");
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
	world_parse(world, filename, fd);
	close(fd);
	return (world);
}
