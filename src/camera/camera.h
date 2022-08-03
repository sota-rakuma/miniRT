#ifndef CAMERA_H
#define CAMERA_H

typedef struct s_vec3d	t_vec3d;

// camera
typedef struct s_camera {
	t_vec3d	pos;
	t_vec3d normal;
	double	fov;

	// スクリーンの左上（スタートポジション）
	t_vec3d screen_start_pos;
	t_vec3d screen_vertical_normal;
	t_vec3d screen_horizon_normal;
	double screen_height;
	double screen_width;
	double dx;
	double dy;
} t_camera;

void	camera_set(t_camera *camera);

#endif /* CAMERA_H */
