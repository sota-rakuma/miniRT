#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "ImageData.h"

t_image_data	*init_image_data(void *mlx, int height, int width)
{
	t_image_data	*new;

	new = (t_image_data *)malloc(sizeof(t_image_data));
	if (new == NULL)
	{
		printf("failed to initialize image data\n");
		exit(1);
	}
	new->_img = mlx_new_image(mlx, width, height);
	if (new->_img == NULL) {
		printf("faild to make new image\n");
		exit(1);
	}
	new->_addr = mlx_get_data_addr(new->_img, &(new->_bits_per_pixel), \
										&(new->_line_length), &(new->_endian));
	return (new);
}

static void	my_mlx_pixel_put(t_image_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->_addr + (y * data->_line_length + x * (data->_bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


// create_triangleで実装したい
void	create_square(t_image_data *data, int height, int width, int color)
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			my_mlx_pixel_put(data, i, j, color);
		}
	}
}

void	destruct_image_data(void *mlx, t_image_data *data)
{
	mlx_destroy_image(mlx, data->_img);
	free(data);
}
