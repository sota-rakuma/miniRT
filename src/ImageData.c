#include "ImageData.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

t_image_data* init_image_data(void* mlx, int height, int width) {
	t_image_data* new;

	new = (t_image_data*)malloc(sizeof(t_image_data));
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

static void my_mlx_pixel_put(t_image_data* data, int x, int y, int color) {
	char* dst;

	dst = data->_addr +
	      (y * data->_line_length + x * (data->_bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static int absolute(int x) {
	if (x < 0)
		return (-x);
	return (x);
}

static int init_line_data(t_coordinate* start, t_coordinate* end,
                          t_coordinate* delta, t_coordinate* steep) {
	if (!start || !end)
		return (1);
	delta->x = absolute(end->x - start->x);
	delta->y = absolute(end->y - start->y);
	if (start->x >= end->x)
		steep->x = -1;
	else
		steep->x = 1;
	if (start->y >= end->y)
		steep->y = -1;
	else
		steep->y = 1;
	return (0);
}

/**
 * @brief Bresenham's line algorithm, it is draw line from start to end
 * if return value more than 1 it is failed to draw line for some reason,
 * othrewise it is ok
 *
 * @param start
 * @param end
 * @param data data of image
 * @param color
 */
int draw_line(t_coordinate* start, t_coordinate* end, t_image_data* data,
              t_color color) {
	t_coordinate delta;
	t_coordinate tmp;
	t_coordinate steep;
	int error;

	if (init_line_data(start, end, &delta, &steep))
		return (1);
	tmp   = (t_coordinate){start->x, start->y};
	error = delta.x - delta.y;
	while (1) {
		my_mlx_pixel_put(data, tmp.x, tmp.y, color);
		if (tmp.x == end->x && tmp.y == end->y)
			break;
		if ((2 * error) >
		    -delta.y) // Whether adding delta.y to the current x coordinate does
		              // not exceed half of the x increase
		{
			error -= delta.y;
			tmp.x += steep.x;
		}
		if ((2 * error) <
		    delta
		        .x) // If it is exceeded, add 1 to the y-coordinate and add x to
		//  error again to take into account the slope.
		{
			error += delta.x;
			tmp.y += steep.y;
		}
	}
	return (0);
}

int draw_circle(t_coordinate* center, unsigned int radius, t_image_data* data,
                t_color color) {
	if (center == NULL)
		return (1);
	if (center->x < radius || center->y < radius ||
	    WIDTH < (center->x + radius) || HEIGHT < (center->y + radius))
		return (2);

	t_coordinate now = (t_coordinate){radius, 0};
	while (absolute(now.x) >= absolute(now.y)) {
		my_mlx_pixel_put(data, center->x + now.x, center->y + now.y, color);
		my_mlx_pixel_put(data, center->x - now.x, center->y + now.y, color);
		my_mlx_pixel_put(data, center->x + now.x, center->y - now.y, color);
		my_mlx_pixel_put(data, center->x - now.x, center->y - now.y, color);
		my_mlx_pixel_put(data, center->x + now.y, center->y + now.x, color);
		my_mlx_pixel_put(data, center->x - now.y, center->y + now.x, color);
		my_mlx_pixel_put(data, center->x + now.y, center->y - now.x, color);
		my_mlx_pixel_put(data, center->x - now.y, center->y - now.x, color);
		// 下
		long double dist1 =
		    (now.x) * (now.x) + (now.y + 1) * (now.y + 1) - radius * radius;
		// 左下
		long double dist2 = (now.x - 1) * (now.x - 1) +
		                    (now.y + 1) * (now.y + 1) - radius * radius;
		now.y++;
		if (dist1 > dist2)
			now.x--;
	}
	return 0;
}

// int draw_circle(t_coordinate *center, unsigned int radius, t_image_data
// *data, 				t_color color)
// {
// 	t_coordinate start;
// 	t_coordinate tmp;
// 	int error;
// 	int x_coefficient;

// 	if (center == NULL)
// 		return (1);
// 	if (center->x < radius || center->y < radius ||
// 		WIDTH < (center->x + radius) || HEIGHT < (center->y + radius))
// 		return (2);
// 	// start = (t_coordinate){center->x - radius, center->y};
// 	start = (t_coordinate){center->x + radius, center->y};
// 	//   tmp = start;
// 	tmp = (t_coordinate){start.x, start.y};
// 	x_coefficient = 1;
// 	int y_coff = 1;
// 	error = 5;
// 	while (2 * tmp.y != (2 * start.y) + radius)
// 	{
// 		my_mlx_pixel_put(data, tmp.x, tmp.y, color);
// 		if (error > 0)
// 		{
// 			x_coefficient += 2;
// 			// error += (x_coefficient * tmp.x - center->x + 2) << 2;
// 			error -= (x_coefficient * tmp.x - center->x) << 2;
// 			error += 8;
// 			//  tmp.x++;
// 			tmp.x--;
// 		}
// 		tmp.y++;
// 		y_coff += 2;
// 		error += ((tmp.y - center->y) + y_coff) << 3;
// 		printf("error : %d\n center->x: %d, tmp.x: %d\n center->y: %d, tmp.y: "
// 			   "%d\n",
// 			   error, center->x, tmp.x, center->y, tmp.y);
// 	}
// 	return (0);
// }

// create_triangleで実装したい
void create_square(t_image_data* data, int height, int width, int color) {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			my_mlx_pixel_put(data, i, j, color);
		}
	}
}

void destruct_image_data(void* mlx, t_image_data* data) {
	mlx_destroy_image(mlx, data->_img);
	free(data);
}
