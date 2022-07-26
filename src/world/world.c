#include "../minirt.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

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

bool world_check(t_world *world) {
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
		if (ft_strcmp(strs[0], "A") == 0) {
			if (!check_strs_len(strs, 3)) {
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
		// Camera
		else if (ft_strcmp(strs[0], "C") == 0) {
			if(!check_strs_len(strs, 4)) {
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
		// Light
		else if (ft_strcmp(strs[0], "L") == 0) {
			if (check_strs_len(strs, 3)) {
				t_light *light = malloc(sizeof(t_light));
				light->kind = LIGHT;

				long i = 1;
				light->pos = parse_vec3d(strs[i++]);
				light->intensity = parse_num(strs[i++]);
				light->color = (t_color){255.0, 255.0, 255.0};
				world_add_light(world, light);
			}
			else if (check_strs_len(strs, 4)) {
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
		// Sphere
		else if (ft_strcmp(strs[0], "sp") == 0) {
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

			// printf("shape: center: %f, %f, %f\n", shape->center.x, shape->center.y, shape->center.z);
			// printf("shape: radius: %f\n", shape->radius);
			// printf("shape: color: %f, %f, %f\n", shape->color.r, shape->color.g, shape->color.b);
			world_add_shape(world, shape);
		}
		// Plane
		else if (ft_strcmp(strs[0], "pl") == 0) {
			if(!check_strs_len(strs, 4)) {
				printf("column error: %ld\n", row);
				exit(1);
			}
			t_shape *shape = malloc(sizeof(t_shape));
			shape->kind =PLANE;

			long i = 1;
			shape->point =	parse_vec3d(strs[i++]);
			shape->oriental_normal = parse_vec3d(strs[i++]);
			shape->color = parse_color(strs[i++]);

			shape->ka = color_mult_num(shape->color, 1.0 / 255.0); // 環境光反射係数
        	shape->kd = color_mult_num(shape->color, 1.0 / 255.0 * 0.69);   // 拡散反射係数
        	// shape->kd = (t_color){0.0, 0.69, 0.0};   // 拡散反射係数
        	shape->ks = (t_color){0.3, 0.3, 0.3};    // 鏡面反射係数
			shape->shininess = 16.0;                  //光沢度
			world_add_shape(world, shape);
		}
		// Cylinder
		else if (ft_strcmp(strs[0], "cy") == 0) {
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

// ワールド情報は現状直接書いてる
// TODO: パースした情報を入れる
t_world	*world_init(char *filename) {
	t_world *world;

	world = malloc(sizeof(t_world));
	world->shape_list = NULL;
	world->light_list = NULL;

	world->bg = (t_color){30.0, 30.0, 30.0};

	world_parse(world, filename);

	{
		t_camera *camera= malloc(sizeof(t_camera));
		// *camera = (t_camera){(t_vec3d){0, 0, -5}, 0.0};
		camera->pos = world->camera->pos;
		camera->normal = world->camera->normal;
		camera->fov = world->camera->fov;

		// normalを単位ベクトルに変換
		camera->normal = vec3d_mult(camera->normal, 1.0 / vec3d_length(camera->normal));
		// fovをラジアンに変換
		camera->fov = M_PI * camera->fov / 180.0;

		// カメラからスクリーンの距離
		double d = 1.0;
		// スクリーン中心から端までの距離
		double horizen_d = d * tan(camera->fov / 2.0);
		double vertical_d = horizen_d * (double)HEIGHT / (double)WIDTH;

		camera->screen_height = 2.0 * vertical_d;
		camera->screen_width = 2.0 * horizen_d;

		// スクリーンの左右両端の点を求める--------------------------
		// カメラからnormal方向にdだけ離れた位置の点
		t_vec3d screen_center_pos = vec3d_add(camera->pos, vec3d_mult(camera->normal, d));

		// 横幅のずらす距離
		t_vec3d screen_left_pos = vec3d_add(screen_center_pos, (t_vec3d){-1 * horizen_d, 0, 0});
		t_vec3d screen_right_pos = vec3d_add(screen_center_pos, (t_vec3d){horizen_d, 0, 0});

		// スクリーンの左上、右上、左下の点を求める-----------------
		t_vec3d screen_o_to_left = vec3d_sub(screen_left_pos, screen_center_pos);
		t_vec3d camera_to_screen_o = vec3d_sub(screen_center_pos, camera->pos);
		t_vec3d vertical_normal = vec3d_cross(camera_to_screen_o, screen_o_to_left);
		vertical_normal = vec3d_mult(vertical_normal, 1.0 / vec3d_length(vertical_normal));

		camera->screen_start_pos = vec3d_sub(screen_left_pos, vec3d_mult(vertical_normal, vertical_d));
		camera->screen_horizon_normal = (t_vec3d){1, 0, 0};
		camera->screen_vertical_normal = vec3d_mult(vertical_normal, 1.0 / vec3d_length(vertical_normal));

		// サンプル
		// camera->screen_width = 2.0;
		// camera->screen_height = 2.0;
		printf("start: %f, %f, %f\n", camera->screen_start_pos.x, camera->screen_start_pos.y, camera->screen_start_pos.z);
		printf("horizon: %f, %f, %f\n", camera->screen_horizon_normal.x, camera->screen_horizon_normal.y, camera->screen_horizon_normal.z);
		printf("vertical: %f, %f, %f\n", camera->screen_vertical_normal.x, camera->screen_vertical_normal.y, camera->screen_vertical_normal.z);
		// camera->screen_start_pos = (t_vec3d){-1, 1, 0};
		// camera->screen_horizon_normal = (t_vec3d){1, 0, 0};
		// camera->screen_vertical_normal = (t_vec3d){s0, -1, 0};

		world->camera = camera;
	}

	return world;
}
