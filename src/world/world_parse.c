#include "../minirt.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>


bool world_check(t_world *world)
{
	// 存在チェック： A, C, L
	return true;
}

long	strs_len(char **strs)
{
	long	i;

	i = 0;
	while (strs[i])
		i++;
	return i;
}

double parse_num(char *str) {
	double integer;
	double decimal;
	double sign;
	double digit;
	long i;

	i = 0;
	integer = 0;
	decimal = 0;
	digit = 1;

	sign = 1.0;
	if (str[i] == '-' || str[i] == '+')
		sign = 1.0 - 2.0 * (str[i++] == '-');
	while (ft_isdigit(str[i])) {
		integer = integer * 10 + (double)(str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i])) {
		decimal = decimal * 10 + (double)(str[i] - '0');
		digit *= 10;
		i++;
	}
	if (str[i] != '\0') {
		printf("parse_num error: %s\n", str);
		exit(1);
	}
	return sign * (integer + decimal / digit);
}

void	free_all(char **strs)
{
	long	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

t_vec3d	parse_vec3d(char *str)
{
	char	**strs;
	long	len;
	t_vec3d	vec;

	strs = ft_split(str, ',');
	len = strs_len(strs);
	if (len != 3)
	{
		printf("in parse vec3d, the number of elements: %ld Error\n", len);
		free_all(strs);
		exit(1);
	}
	vec.x = parse_num(strs[0]);
	vec.y = parse_num(strs[1]);
	vec.z = parse_num(strs[2]);
	free_all(strs);
	return (vec);
}

t_color	parse_color(char *str)
{
	char	**strs;
	long	len;
	t_color	color;

	strs = ft_split(str, ',');
	len = strs_len(strs);
	if (len != 3)
	{
		printf("in parsing color, the number of elements: %ld Error\n", len);
		free_all(strs);
		exit(1);
	}
	color.r = parse_num(strs[0]);
	color.g = parse_num(strs[1]);
	color.b = parse_num(strs[2]);
	free_all(strs);
	return (color);
}

void	world_parse_ambient_light(t_world *world, char **strs)
{
	t_light	*light;
	long	len;

	len = strs_len(strs);
	if (len != 3)
	{
		printf("in %s, the number of elements: %ld Error\n", __func__, len);
		free_all(strs);
		exit(1);
	}
	light = malloc((t_light *)sizeof(t_light));
	if (light == NULL)
	{
		printf("in %s, failed to malloc\n", __func__);
		free_all(strs);
		exit(1);
	}
	light->kind = AMBIENT_LIGHT;
	light->intensity = parse_num(strs[1]);
	light->color = parse_color(strs[2]);
	world_add_light(world, light);
}

void	world_parse_light(t_world *world, char **strs)
{
	long	len;
	t_light	*light;

	len = strs_len(strs);
	if (len != 3 && len != 4)
	{
		printf("in %s, the number of elements: %ld Error\n", __func__, len);
		free_all(strs);
		exit(1);
	}
	light = malloc(sizeof(t_light));
	if (light == NULL)
	{
		printf("in %s, failed to malloc\n", __func__);
		free_all(strs);
		exit(1);
	}
	light->kind = LIGHT;
	light->pos = parse_vec3d(strs[1]);
	light->intensity = parse_num(strs[2]);
	if (len == 3)
		light->color = (t_color){255.0, 255.0, 255.0};
	world_add_light(world, light);
}

void	world_parse_camera(t_world *world, char **strs)
{
	long		len;
	t_camera	*camera;

	len = strs_len(strs);
	if (len != 4)
	{
		printf("in %s, the number of elements: %ld Error\n", __func__, len);
		free_all(strs);
		exit(1);
	}
	camera = malloc((t_camera *)sizeof(t_camera));
	if (camera == NULL)
	{
		printf("in %s, failed to malloc\n", __func__);
		free_all(strs);
		exit(1);
	}
	world->camera = camera;
	camera->pos = parse_vec3d(strs[1]);
	camera->normal = parse_vec3d(strs[2]);
	camera->fov = parse_num(strs[3]);
}

void	world_parse_sphere(t_world *world, char **strs)
{
	long	len;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 4)
	{
		printf("in %s, the number of elements: %ld Error\n", __func__, len);
		free_all(strs);
		exit(1);
	}
	shape = (t_shape *)malloc(sizeof(t_shape));
	if (shape == NULL)
	{
		printf("in %s, failed to malloc\n", __func__);
		free_all(strs);
		exit(1);
	}
	shape->kind = SPHERE;
	shape->center =	parse_vec3d(strs[1]);
	shape->radius =	parse_num(strs[2]) / 2.0;
	shape->color = parse_color(strs[3]);
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	world_add_shape(world, shape);
}

void	world_parse_plane(t_world *world, char **strs)
{
	long	len;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 4 && (len != 5 || ft_strcmp(strs[4], "mirror")))
	{
		printf("in %s, the number of elements: %ld Error\n", __func__, len);
		free_all(strs);
		exit(1);
	}
	t_shape *shape = (t_shape *)malloc(sizeof(t_shape));
	if (shape == NULL)
	{
		printf("in %s, failed to malloc\n", __func__);
		free_all(strs);
		exit(1);
	}
	shape->kind = PLANE;
	shape->point = parse_vec3d(strs[1]);
	shape->oriental_normal = parse_vec3d(strs[2]);
	shape->color = parse_color(strs[3]);
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	if (check_strs_len(strs, 5))
		shape->is_mirror = true;
	world_add_shape(world, shape);
}

void world_parse_cylinder(t_world *world, char **strs)
{
	long	len;
	t_shape	*shape;

	len = strs_len(strs);
	if(len != 6)
	{
		printf("in %s, the number of elements: %ld Error\n", __func__, len);
		free_all(strs);
		exit(1);
	}
	t_shape *shape = (t_shape *)malloc(sizeof(t_shape));
	if (shape == NULL)
	{
		printf("in %s, failed to malloc\n", __func__);
		free_all(strs);
		exit(1);
	}
	shape->kind = CYLINDER;
	shape->center =	parse_vec3d(strs[1]);
	shape->oriental_normal = parse_vec3d(strs[2]);
	shape->radius =	parse_num(strs[3]) / 2.0;
	shape->height =	parse_num(strs[4]);
	shape->color = parse_color(strs[5]);
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	world_add_shape(world, shape);
}

void	world_parse(t_world *world, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("cannot open file\n");
		exit(1);
	}
	while (true)
	{
		line = get_next_line(fd);
		if(line == NULL)
			break;
		if(line[0] == '\0')
		{
			free(line);
			continue;
		}
		char **strs = ft_split(line, ' ');
		if (strs == NULL)
		{
			printf("in %s, failed to malloc\n", __func__);
			exit(1);
		}

		if (ft_strcmp(strs[0], "A") == 0)
			world_parse_ambient_light(world, strs);
		else if (ft_strcmp(strs[0], "C") == 0)
			world_parse_camera(world, strs);
		else if (ft_strcmp(strs[0], "L") == 0)
			world_parse_light(world, strs);
		else if (ft_strcmp(strs[0], "sp") == 0)
			world_parse_sphere(world, strs);
		else if (ft_strcmp(strs[0], "pl") == 0)
			world_parse_plane(world, strs);
		else if (ft_strcmp(strs[0], "cy") == 0)
			world_parse_cylinder(world, strs);
		else
		{
			printf("not exist keyword: %s", strs[0]);
			free(line);
			exit(1);
		}
		free(line);
	}
	if (!world_check(world)) {
		printf("parse error\n");
		exit(1);
	}
}
