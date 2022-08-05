#include "../minirt.h"

bool	world_check(t_world *world)
{
	t_light	*light;
	bool	a;
	bool	l;

	light = world->light_list;
	a = false;
	l = false;
	while (light)
	{
		if (light->kind == AMBIENT_LIGHT)
		{
			if (a == false)
				a = true;
			else
				return (false);
		}
		else
			l = true;
		light = light->next;
	}
	return (a && l && (world->camera));
}

long	strs_len(char **strs)
{
	long	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	*ft_xalloc(size_t count, size_t size, const char *func_name)
{
	size_t	ratio;
	size_t	len;
	void	*ptr;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	ratio = ULONG_MAX / size;
	if (count > ratio)
		len = ULONG_MAX;
	else
		len = size * count;
	ptr = malloc(len);
	if (ptr == NULL)
	{
		printf("in %s, failed to malloc", func_name);
		exit(1);
	}
	return (ptr);
}

double	parse_num(char *str)
{
	double	integer;
	double	sign;
	double	digit;
	long	i;

	i = 0;
	integer = 0;
	digit = 10;
	sign = 1.0;
	if (str[i] == '-' || str[i] == '+')
		sign = 1.0 - 2.0 * (str[i++] == '-');
	while (ft_isdigit(str[i]))
		integer = integer * 10 + (double)(str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		integer += (double)(str[i++] - '0') / digit;
		digit *= 10;
	}
	if (str[i] != '\0')
	{
		printf("parse_num error: %s\n", str);
		exit(1);
	}
	return (sign * integer);
}

void	free_all(char **strs)
{
	long	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	number_of_element_error(
	char **strs,
	const char *func_name,
	long len)
{
	printf("in %s, the number of elements: %ld Error\n", func_name, len);
	free_all(strs);
	exit(1);
}

bool	check_in_range(double val[], size_t len, double max, double min)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (val[i] < min || max < val[i])
			return (false);
		i++;
	}
	return (true);
}

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

bool	check_num_of_elements(char *str)
{
	char	*commma;
	long	cnt;

	cnt = 0;
	commma = str;
	while (true)
	{
		commma = ft_strchr(commma, ',');
		if (commma == NULL)
			break ;
		commma++;
		cnt++;
	}
	return (cnt == 2);
}

t_vec3d	parse_vec3d(char *str)
{
	char	**strs;
	long	len;
	t_vec3d	vec;

	if (!check_num_of_elements(str))
	{
		printf("Wrong number of elements\n");
		exit(1);
	}
	strs = ft_split(str, ',');
	len = strs_len(strs);
	if (len != 3)
		number_of_element_error(strs, __func__, len);
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

	if (!check_num_of_elements(str))
	{
		printf("Wrong number of elements\n");
		exit(1);
	}
	strs = ft_split(str, ',');
	len = strs_len(strs);
	if (len != 3)
		number_of_element_error(strs, __func__, len);
	color.r = parse_num(strs[0]);
	color.g = parse_num(strs[1]);
	color.b = parse_num(strs[2]);
	if (!check_in_range((double []){color.r, color.g, color.b}, 3, 255.0, 0.0))
	{
		printf("color is out of range\n");
		exit(1);
	}
	free_all(strs);
	return (color);
}

void	world_parse_ambient_light(t_world *world, char **strs)
{
	long	len;
	t_light	*light;

	len = strs_len(strs);
	if (len != 3)
		number_of_element_error(strs, __func__, len);
	light = (t_light *)ft_xalloc(sizeof(t_light), 1, __func__);
	light->kind = AMBIENT_LIGHT;
	light->intensity = parse_num(strs[1]);
	if (light->intensity < 0.0 || 1.0 < light->intensity)
	{
		printf("brightness of ambient light is out of range\n");
		exit(1);
	}
	light->color = parse_color(strs[2]);
	world_add_light(world, light);
}

void	world_parse_light(t_world *world, char **strs)
{
	long	len;
	t_light	*light;

	len = strs_len(strs);
	if (len != 3 && len != 4)
		number_of_element_error(strs, __func__, len);
	light = (t_light *)ft_xalloc(sizeof(t_light), 1, __func__);
	light->kind = LIGHT;
	light->pos = parse_vec3d(strs[1]);
	light->intensity = parse_num(strs[2]);
	if (light->intensity < 0.0 || 1.0 < light->intensity)
	{
		printf("brightness of light is out of range\n");
		exit(1);
	}
	if (len == 3)
		light->color = (t_color){255.0, 255.0, 255.0};
	else
		light->color = parse_color(strs[3]);
	world_add_light(world, light);
}

void	world_parse_camera(t_world *world, char **strs)
{
	long		len;
	double		*tmp;
	t_camera	*camera;

	if (world->camera)
	{
		printf("Two or more C's exist\n");
		exit(1);
	}
	len = strs_len(strs);
	if (len != 4)
		number_of_element_error(strs, __func__, len);
	camera = (t_camera *)ft_xalloc(sizeof(t_camera), 1, __func__);
	world->camera = camera;
	camera->pos = parse_vec3d(strs[1]);
	camera->normal = parse_vec3d(strs[2]);
	tmp = (double []){camera->normal.x, camera->normal.y, camera->normal.z};
	if (!check_in_range(tmp, 3, 1.0, -1.0))
	{
		printf("camera's normal is out of range\n");
		exit(1);
	}
	camera->fov = parse_num(strs[3]);
	if (camera->fov < 0.0 || 180.0 < camera->fov)
	{
		printf("camera's fov is out of range\n");
		exit(1);
	}
}

void	world_parse_sphere(t_world *world, char **strs)
{
	long	len;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 4)
		number_of_element_error(strs, __func__, len);
	shape = (t_shape *)ft_xalloc(sizeof(t_shape), 1, __func__);
	shape->kind = SPHERE;
	shape->center = parse_vec3d(strs[1]);
	shape->radius = parse_num(strs[2]) / 2.0;
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
	double	*tmp;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 4 && (len != 5 || ft_strcmp(strs[4], "mirror")))
		number_of_element_error(strs, __func__, len);
	shape = (t_shape *)ft_xalloc(sizeof(t_shape), 1, __func__);
	shape->kind = PLANE;
	shape->point = parse_vec3d(strs[1]);
	shape->normal = parse_vec3d(strs[2]);
	tmp = (double []){shape->normal.x, shape->normal.y, shape->normal.z};
	if (!check_in_range(tmp, 3, 1.0, -1.0))
	{
		printf("sphere's normal is out of range\n");
		exit(1);
	}
	shape->color = parse_color(strs[3]);
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	if (len == 5)
		shape->is_mirror = true;
	world_add_shape(world, shape);
}

void	world_parse_cylinder(t_world *world, char **strs)
{
	long	len;
	double	*tmp;
	t_shape	*shape;

	len = strs_len(strs);
	if (len != 6)
		number_of_element_error(strs, __func__, len);
	shape = (t_shape *)ft_xalloc(sizeof(t_shape), 1, __func__);
	shape->kind = CYLINDER;
	shape->center = parse_vec3d(strs[1]);
	shape->normal = parse_vec3d(strs[2]);
	tmp = (double []){shape->normal.x, shape->normal.y, shape->normal.z};
	if (!check_in_range(tmp, 3, 1.0, -1.0))
	{
		printf("cylinder's normal is out of range\n");
		exit(1);
	}
	shape->radius = parse_num(strs[3]) / 2.0;
	shape->height = parse_num(strs[4]);
	shape->color = parse_color(strs[5]);
	shape->ka = color_mult_num(shape->color, 1.0 / 255.0);
	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);
	shape->ks = (t_color){0.3, 0.3, 0.3};
	shape->shininess = 16.0;
	world_add_shape(world, shape);
}

void	world_parse_line(t_world *world, char **strs)
{
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
		printf("not exist keyword: %s\n", strs[0]);
		exit(1);
	}
}

void	world_parse(t_world *world, int fd)
{
	char	*line;
	char	**strs;

	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (line[0] != '\0')
		{
			strs = ft_split(line, ' ');
			if (strs == NULL)
			{
				printf("in %s, failed to malloc\n", __func__);
				free(line);
				exit(1);
			}
			world_parse_line(world, strs);
			free_all(strs);
		}
		free(line);
	}
	if (!world_check(world))
	{
		printf("parse error\n");
		exit(1);
	}
}
