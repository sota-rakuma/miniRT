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

int convert_color(t_color c) {
	return ((int)c.r << 16 | (int)c.g << 8 | (int)c.b);
}

// 第1回
	// <P-C, P-C> = r^2 // 球
	// P = O + tD       // 視線上の任意の点

	// 計算過程
	// <O + tD -C, O + tD -C>   = r^2 
	// <O - C + tD, O - C + tD> = r^2
	// <CO + tD, CO + tD> = r^2

	// <CO, CO> + 2t<D, CO> + t^2 <D, D> - r^2 = 0 
	// a * t^2 + b * t + c = 0
	// t = <解の公式>  

	// t < 0: カメラより後ろ
	// 0 <= t <= 1: カメラとスクリーンの間
	// 1 < t: スクリーンの向こう側

	// 交差条件: tが実数(D >= b^2 - 4ac) && t > 1 

	// 交差条件を満たす物体が2つの場合
	// 	-> tが小さい方がスクリーンに映る

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
		screen_p.y = (max_p - min_p) / (double)height * (double)y + min_p;
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

			// 交差判定
			bool flag = (discriminant >= 0);

			// 出力	
			// 	交差したら球色
			// 	交差しなかったら背景色
			if (flag)
				img_pixel_put(screen->_img, x, y, convert_color(sp.color));
			else
				img_pixel_put(screen->_img, x, y, convert_color(bg));
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
