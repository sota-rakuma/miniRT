#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#define WIDTH 500
#define HEIGHT 500

#include "Color.h"

typedef struct s_image_data
{
	void	*_img;
	char	*_addr;
	int		_bits_per_pixel;
	int		_line_length;
	int		_endian;
}				t_image_data;

typedef struct s_coordinate
{
	int	x;
	int	y;
#ifdef THREE_DIMENTION
	int	z;
#endif
}				t_coordinate;

t_image_data	*init_image_data(void *mlx, int height, int width);
void			create_square(t_image_data *data, \
								int height, int width, int color);
int				draw_line(t_coordinate *start, t_coordinate *end, \
								t_image_data *data, t_color color);
int				draw_circle(t_coordinate *center, unsigned int radius, \
								t_image_data *data, t_color color);
void			destruct_image_data(void *mlx, t_image_data *data);

#endif /* IMAGEDATA_H */
