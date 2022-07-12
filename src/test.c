#include "Color.h"
#include "ForMapping.h"
#include "Win.h"
#include <math.h>
#include <stdio.h>

int key_event(int key_code, void* param) {
	printf("key_code: %d\n", key_code);
	if (key_code == 65307)
		exit(0);
}

int main(void) {
	void* mlx = mlx_init();
	if (mlx == NULL) {
		printf("initialized mlx error\n");
		exit(0);
	}
	void* win       = init_win(mlx, "hello world");
	t_for_map* data = init_data_for_mapping(mlx, win);

	int height = HEIGHT;
	int width  = WIDTH;

	t_image_data* img = init_image_data(data->_mlx, HEIGHT, WIDTH);
	t_frame* frame    = init_frame(img, (t_coordinate){0, 0});
	// draw_line(&b, &a, (t_image_data *)(frame->_img), 0x00ff0000);
	add_frame(data, frame);

	mlx_loop_hook(mlx, get_animation, data);
	mlx_key_hook(win, key_event, data);
	mlx_loop(mlx);
	return (0);
}