#include "minirt.h"

int key_event(int key_code, void *param)
{
	printf("key_code: %d\n", key_code);
	if (key_code == 65307)
		exit(0);
	return (0);
}

typedef struct s_color {
	double r;
	double g;
	double b;
} t_color;

typedef struct s_vec3d {
	double x;
	double y;
	double z;
} t_vec3d;

typedef struct s_sphere {
	t_vec3d center;
	double radius;
	t_color color;
} t_sphere;

double dot(t_vec3d a, t_vec3d b) {
	return a.x * b.x + a.y * b.y + a.z * b.z; 
}

t_vec3d sub(t_vec3d a, t_vec3d b) {
	t_vec3d ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

t_vec3d add(t_vec3d a, t_vec3d b) {
	t_vec3d ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

t_vec3d mult(t_vec3d a, double n) {
	return (t_vec3d){a.x * n, a.y * n, a.z * n};
}

double length(t_vec3d a) {
	return sqrt(dot(a, a));
}

int convert_color(t_color c) {
	return ((int)c.r << 16 | (int)c.g << 8 | (int)c.b);
}



typedef struct s_light {
	t_vec3d	pos;
} t_light;

int main(void)
{
	void *mlx = mlx_init();
	if (mlx == NULL)
	{
		printf("initialized mlx error\n");
		exit(0);
	}
	// void *win = win_init(mlx, "hello world");

	t_screen *screen = screen_init("miniRT");

	int height = HEIGHT;
	int width = WIDTH;

	// 視点の位置を決める
	t_vec3d camera = (t_vec3d){0, 0, -5};

	// 球
	t_sphere sp;
	sp.center = (t_vec3d){0, 0, 5};
	sp.radius = 1.0;
	sp.color = (t_color){255.0, 0.0, 0.0};

	// 点光源
	t_light light;
	light.pos = (t_vec3d){-5.0, 5.0, -5.0};

	// 背景
	t_color bg = (t_color){0.0, 0.0, 255.0};

	// スクリーン上の点
	t_vec3d screen_p;
	screen_p.z = 0;
	double min_p = -1.0;
	double max_p = 1.0;

	// forで回す
	long y;
	long x;
	
	y = 0;
	while (y < height) {
		screen_p.y = max_p - ((max_p - min_p) / (double)height * (double)y);
		x = 0;
		while (x < width) {
			screen_p.x = (max_p - min_p) / (double)width * (double)x + min_p;
			// 視線ベクトル
			t_vec3d d = sub(screen_p, camera);
			
			// 視点 - 球の中心 ベクトル
			t_vec3d co = sub(camera, sp.center);

			double a = dot(d, d);
			double b = 2 * dot(d, co);
			double c = dot(co, co) - sp.radius * sp.radius;

			double discriminant = b * b - 4 * a * c;

			double t = -1;
			if (discriminant == 0)
				t = - b / (2 * a);
			else if (discriminant > 0) {
				double t1 = (- b - sqrt(discriminant)) / (2 * a);
				double t2 = (- b + sqrt(discriminant)) / (2 * a);
				double t_min = t1 > t2 ? t2 : t1;
				double t_max = t1 > t2 ? t1 : t2;
				t = t1 > 0 && t2 > 0 ? t_min : t_max;
			}

			// 光の強度
			double intensity = 0.0;
			if (t > 0) {
				// 交差位置: 球面上の点 P = O + tD
				t_vec3d int_pos = add(camera, mult(d, t));
				// 入射ベクトル: 点光源 - 交差位置
				//  -> 単位ベクトル
				t_vec3d light_dir = sub(light.pos, int_pos);
				light_dir = mult(light_dir, 1.0 / length(light_dir));
				// 法線ベクトル: 交差位置(球面上の点) - 球中心
				//  -> 単位ベクトル
				t_vec3d normal = sub(int_pos, sp.center);
				normal = mult(normal, 1.0 / length(normal));

				// dot(入射ベクトル, 法線ベクトル) = |入射ベクトル||法線ベクトル|cosA
				//  = 1 * 1 * cosA = cosA
				double cosA = dot(light_dir, normal);
				cosA = cosA >= 0 ? cosA : 0.0;
				intensity = cosA;
			}
			t_color screen_color;
			if (t > 0) {
				screen_color = (t_color){sp.color.r * intensity, sp.color.g * intensity, sp.color.b * intensity};
			} else {
				screen_color = bg;
			}
			img_pixel_put(screen->_img, x, y, convert_color(screen_color));


			// 交差判定
			// bool flag = (discriminant >= 0);

			// 出力	
			// 	交差したら球色
			// 	交差しなかったら背景色
			// if (flag)
			// 	img_pixel_put(screen->_img, x, y, convert_color(sp.color));
			// else
			// 	img_pixel_put(screen->_img, x, y, convert_color(bg));
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(screen->_mlx, screen->_win,
								screen->_img->_img, 0, 0);

	mlx_key_hook(screen->_win, key_event, NULL);
	mlx_loop(screen->_mlx);
	return (0);
}
