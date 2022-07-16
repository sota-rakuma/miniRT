#include "minirt.h"

int key_event(int key_code, void *param)
{
	printf("key_code: %d\n", key_code);
	if (key_code == 65307)
		exit(0);
	return (0);
}

typedef struct s_sphere {
	t_vec3d center;
	double radius;
	t_color color;
} t_sphere;

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
	sp.color = (t_color){255.0, 255.0, 255.0};

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
			t_vec3d d = vec3d_sub(screen_p, camera);

			// 視点 - 球の中心 ベクトル
			t_vec3d co = vec3d_sub(camera, sp.center);

			double a = vec3d_dot(d, d);
			double b = 2 * vec3d_dot(d, co);
			double c = vec3d_dot(co, co) - sp.radius * sp.radius;

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

			// パラメータ
			t_color ka = (t_color){0.01, 0.01, 0.01}; // 環境光反射係数
			t_color kd = (t_color){0.69, 0.0, 0.0}; // 拡散反射係数
			t_color ks = (t_color){0.3, 0.3, 0.3};;  // 鏡面反射係数
			t_color ia = (t_color){0.1, 0.1, 0.1};;  // 環境光の強度
			t_color ii = (t_color){1.0, 1.0, 1.0};;  // 光源の光の強度
			double alpha = 8.0;    // 光沢度

			// 光の強度
			t_color intensity = (t_color){0.0, 0.0, 0.0};

			// 環境光
			t_color radience_amb = color_mult_color(ia, ka);
			intensity = color_add_color(intensity, radience_amb);

			if (t > 0) {
				// 交差位置: 球面上の点 P = O + tD
				t_vec3d int_pos = vec3d_add(camera, vec3d_mult(d, t));
				// 入射ベクトル: 点光源 - 交差位置
				//  -> 単位ベクトル
				t_vec3d light_dir = vec3d_sub(light.pos, int_pos);
				light_dir = vec3d_mult(light_dir, 1.0 / vec3d_length(light_dir));
				// 法線ベクトル: 交差位置(球面上の点) - 球中心
				//  -> 単位ベクトル
				t_vec3d normal = vec3d_sub(int_pos, sp.center);
				normal = vec3d_mult(normal, 1.0 / vec3d_length(normal));

				// 拡散反射光 ----------------------------------------
				// vec3d_dot(入射ベクトル, 法線ベクトル) = |入射ベクトル||法線ベクトル|cosA
				//  = 1 * 1 * cosA = cosA
				double cosA = vec3d_dot(light_dir, normal);
				cosA = cosA >= 0 ? cosA : 0.0;
				t_color radience_dif = color_mult_num(
						color_mult_color(kd, ii), cosA);
				intensity = color_add_color(intensity, radience_dif);

				// 鏡面反射光 ----------------------------------------
				t_color radience_spe = (t_color){0.0, 0.0, 0.0};
				if (cosA > 0)
				{
					//正反射ベクトル
					t_vec3d r = vec3d_sub(vec3d_mult(normal, 2 * (cosA)), light_dir);
					// 視線ベクトルの逆単位ベクトル
					t_vec3d v = vec3d_mult(int_pos, -1.0 * 1.0 / vec3d_length(int_pos));
					// 視線ベクトルの逆単位ベクトルと正反射ベクトルの内積
					double v_dot_r = vec3d_dot(v, r);
					v_dot_r = v_dot_r >= 0 ? v_dot_r : 0.0;
					radience_spe = color_mult_num(
						color_mult_color(ks, ii), pow(v_dot_r, alpha));
				}
				intensity = color_add_color(intensity, radience_spe);
			}
			// [0, 1]に収める
			intensity = color_normalize(intensity);

			t_color screen_color;
			if (t > 0) {
				screen_color = color_mult_num(intensity, 255.0);
			} else {
				screen_color = bg;
			}
			img_pixel_put(screen->_img, x, y, convert_color(screen_color));
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
