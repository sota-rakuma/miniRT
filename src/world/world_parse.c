#include "../minirt.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>


bool world_check(t_world *world) {
	// 存在チェック： A, C, L
	return true;
}

bool check_strs_len(char **strs, long len){
	long i;

	i = 0;
	while (strs[i])
		i++;
	return i == len;
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

t_vec3d parse_vec3d(char *str) {
	char **strs = ft_split(str, ',');
	if (!check_strs_len(strs, 3)) {
		printf("parse_vec3d error\n");
		exit(1);
	}

	t_vec3d vec;
	vec.x = parse_num(strs[0]);
	vec.y = parse_num(strs[1]);
	vec.z = parse_num(strs[2]);
	// free
	return vec;
}

t_color parse_color(char *str) {
	char **strs = ft_split(str, ',');
	if (!check_strs_len(strs, 3)) {
		printf("parse_color error\n");
		exit(1);
	}

	t_color color;
	color.r = parse_num(strs[0]);
	color.g = parse_num(strs[1]);
	color.b = parse_num(strs[2]);
	// free
	return color;
}

void world_parse_ambient_light(t_world *world, char **strs, long row)
{
	if (!check_strs_len(strs, 3))
	{
		printf("column error: %ld\n", row);
		exit(1);
	}
	t_light *light = malloc(sizeof(t_light));
	light->kind = AMBIENT_LIGHT;

	long i = 1;
	light->intensity = parse_num(strs[i++]);
	light->color = parse_color(strs[i++]);
	world_add_light(world, light);
}

void	world_parse_camera(t_world *world, char **strs, long row)
{
	if(!check_strs_len(strs, 4))
	{
		printf("column error: %ld\n", row);
		exit(1);
	}
	t_camera *camera = malloc(sizeof(t_camera));
	world->camera = camera;
	long i = 1;
	camera->pos = parse_vec3d(strs[i++]);
	camera->normal = parse_vec3d(strs[i++]);
	camera->fov = parse_num(strs[i++]);
}

void	world_parse_light(t_world *world, char **strs, long row)
{
	if (check_strs_len(strs, 3))
	{
		t_light *light = malloc(sizeof(t_light));
		light->kind = LIGHT;

		long i = 1;
		light->pos = parse_vec3d(strs[i++]);
		light->intensity = parse_num(strs[i++]);
		light->color = (t_color){255.0, 255.0, 255.0};
		world_add_light(world, light);
	}
	else if (check_strs_len(strs, 4))
	{
		t_light *light = malloc(sizeof(t_light));
		light->kind = LIGHT;

		long i = 1;
		light->pos = parse_vec3d(strs[i++]);
		light->intensity = parse_num(strs[i++]);
		light->color = parse_color(strs[i++]);
		world_add_light(world, light);
	}
	else {
		printf("column error: %ld\n", row);
		exit(1);
	}
}

void world_parse_sphere(t_world *world, char **strs, long row) {
	if(!check_strs_len(strs, 4)) {
		printf("column error: %ld\n", row);
		exit(1);
	}
	t_shape *shape = malloc(sizeof(t_shape));
	shape->kind = SPHERE;

	long i = 1;
	shape->center =	parse_vec3d(strs[i++]);
	shape->radius =	parse_num(strs[i++]) / 2.0;
	shape->color = parse_color(strs[i++]);

	shape->ka = color_mult_num(shape->color, 1.0 / 255.0); // 環境光反射係数
    shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);   // 拡散反射係数
    // shape->kd = (t_color){0.0, 0.69, 0.0};   // 拡散反射係数
    shape->ks = (t_color){0.3, 0.3, 0.3};    // 鏡面反射係数
	shape->shininess = 16.0;                  //光沢度
	world_add_shape(world, shape);
}

void world_parse_plane(t_world *world, char **strs, long row) {
	if(!check_strs_len(strs, 4) && (!check_strs_len(strs, 5) && ft_strcmp(strs[4], "mirror") == 0)) {
		printf("column error: %ld\n", row);
		exit(1);
	}
	t_shape *shape = malloc(sizeof(t_shape));
	shape->kind =PLANE;

	long i = 1;
	shape->point = parse_vec3d(strs[i++]);
	shape->oriental_normal = parse_vec3d(strs[i++]);
	shape->color = parse_color(strs[i++]);

	shape->ka = color_mult_num(shape->color, 1.0 / 255.0); // 環境光反射係数
    shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);   // 拡散反射係数
    // shape->kd = (t_color){0.0, 0.69, 0.0};   // 拡散反射係数
    shape->ks = (t_color){0.3, 0.3, 0.3};    // 鏡面反射係数
	shape->shininess = 16.0;                  //光沢度
	if (check_strs_len(strs, 5))
		shape->is_mirror = true;
	world_add_shape(world, shape);
}

void world_parse_cylinder(t_world *world, char **strs, long row) {
    if(!check_strs_len(strs, 6)) {
		printf("column error: %ld\n", row);
		exit(1);
	}
	t_shape *shape = malloc(sizeof(t_shape));
	shape->kind = CYLINDER;

	long i = 1;
	shape->center =	parse_vec3d(strs[i++]);
	shape->oriental_normal = parse_vec3d(strs[i++]);
	shape->radius =	parse_num(strs[i++]) / 2.0;
	shape->height =	parse_num(strs[i++]);
	shape->color = parse_color(strs[i++]);

	shape->ka = color_mult_num(shape->color, 1.0 / 255.0); // 環境光反射係数
    shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);   // 拡散反射係数
    // shape->kd = (t_color){0.0, 0.69, 0.0};   // 拡散反射係数
    shape->ks = (t_color){0.3, 0.3, 0.3};    // 鏡面反射係数
	shape->shininess = 16.0;                  //光沢度
	world_add_shape(world, shape);
}

void world_parse(t_world *world, char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd <= 0) {
		printf("cant open file\n");
		exit(1);
	}

	long row = -1;
	while (true) {
		char *line = get_next_line(fd);
		if(line == NULL)
			break;
		row++;

		if(line[0] == '\0')
		{
			free(line);
			continue;
		}

		//スペース区切り
		char **strs = ft_split(line, ' ');

		// Ambient Light
		if (ft_strcmp(strs[0], "A") == 0)
			world_parse_ambient_light(world, strs, row);
		// Camera
		else if (ft_strcmp(strs[0], "C") == 0)
			world_parse_camera(world, strs, row);
		// Light
		else if (ft_strcmp(strs[0], "L") == 0)
			world_parse_light(world, strs, row);
		// Sphere
		else if (ft_strcmp(strs[0], "sp") == 0)
            world_parse_sphere(world, strs, row);
		// Plane
		else if (ft_strcmp(strs[0], "pl") == 0)
            world_parse_plane(world, strs, row);
		// Cylinder
		else if (ft_strcmp(strs[0], "cy") == 0)
            world_parse_cylinder(world, strs, row);
		else {
			printf("not exist keyword: %s", strs[0]);
			exit(1);
		}
		free(line);
	}

	if (!world_check(world)) {
		printf("parse error\n");
		exit(1);
	}
}

