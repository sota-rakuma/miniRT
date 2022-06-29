#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#define WIDTH 500
#define HEIGHT 500

typedef struct s_image_data
{
	void	*_img;
	char	*_addr;
	int		_bits_per_pixel;
	int		_line_length;
	int		_endian;
}				t_image_data;

t_image_data	*init_image_data(void *mlx, int height, int width);
void			create_square(t_image_data *data, int height, int width, int color);
void			destruct_image_data(void *mlx, t_image_data *data);

#endif /* IMAGEDATA_H */
