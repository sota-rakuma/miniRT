#include "minirt.h"

t_img* img_init(void* mlx, int height, int width) {
	t_img* new;

	new = (t_img*)malloc(sizeof(t_img));
	if (new == NULL) {
		printf("failed to initialize image data\n");
		exit(1);
	}
	new->_img = mlx_new_image(mlx, width, height);
	if (new->_img == NULL) {
		printf("faild to make new image\n");
		exit(1);
	}
	new->_addr = mlx_get_data_addr(new->_img, &(new->_bits_per_pixel),
	                               &(new->_line_length), &(new->_endian));
	return (new);
}

void img_pixel_put(t_img* data, int x, int y, int color) {
	char* dst;

	dst = data->_addr +
	      (y * data->_line_length + x * (data->_bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void img_destruct(void* mlx, t_img* data) {
	mlx_destroy_image(mlx, data->_img);
	free(data);
}
