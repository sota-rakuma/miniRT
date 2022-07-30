#include "../minirt.h"

void	camera_set(t_camera *camera)
{
	{
		// normalを単位ベクトルに変換
		camera->normal = vec3d_mult(camera->normal, 1.0 / vec3d_length(camera->normal));
		// fovをラジアンに変換
		camera->fov = M_PI * camera->fov / 180.0;

		// カメラからスクリーンの距離
		double d = 1.0;
		// スクリーン中心から端までの距離
		double horizon_d = d * tan(camera->fov / 2.0);
		double vertical_d = horizon_d * (double)HEIGHT / (double)WIDTH;

		camera->screen_height = 2.0 * vertical_d;
		camera->screen_width = 2.0 * horizon_d;
		camera->dx = camera->screen_width / (double)WIDTH;
		camera->dy = camera->screen_height / (double)HEIGHT;

		// スクリーンの左右両端の点を求める--------------------------
		// カメラからnormal方向にdだけ離れた位置の点
		t_vec3d screen_center_pos = vec3d_add(camera->pos, vec3d_mult(camera->normal, d));

		// スクリーンの基底ベクトル
		t_vec3d	w = camera->normal; // z方向
		t_vec3d	a;
		if (w.x < -0.9 || 0.9 < w.x) {
			a = (t_vec3d){0, 1, 0};
		}
		else {
			a = (t_vec3d){1, 0, 0};
		}
		t_vec3d	v = vec3d_cross(a, w); // y方向
		v = vec3d_mult(v, 1.0 / vec3d_length(v));
		t_vec3d	u = vec3d_cross(w, v); // x方向

		// 横幅のずらす距離
		t_vec3d screen_left_pos = vec3d_add(
			screen_center_pos,
			vec3d_mult(u, -1.0 * horizon_d));

		// スクリーンの左上、右上、左下の点を求める-----------------
		t_vec3d screen_o_to_left = vec3d_sub(screen_left_pos, screen_center_pos);
		t_vec3d camera_to_screen_o = vec3d_sub(screen_center_pos, camera->pos);

		camera->screen_start_pos = vec3d_sub(screen_left_pos, vec3d_mult(v, vertical_d));
		camera->screen_horizon_normal = u;
		camera->screen_vertical_normal = v;

		if (camera->fov == 0.0) {
			camera->screen_start_pos = screen_center_pos;
			camera->screen_horizon_normal = (t_vec3d){0, 0, 0};
			camera->screen_vertical_normal = (t_vec3d){0, 0, 0};
		}

		// サンプル
		printf("start: %f, %f, %f\n", camera->screen_start_pos.x, camera->screen_start_pos.y, camera->screen_start_pos.z);
		printf("horizon: %f, %f, %f\n", camera->screen_horizon_normal.x, camera->screen_horizon_normal.y, camera->screen_horizon_normal.z);
		printf("vertical: %f, %f, %f\n", camera->screen_vertical_normal.x, camera->screen_vertical_normal.y, camera->screen_vertical_normal.z);

		// world->camera = camera;
	}
}
