#ifndef IMG_H
# define IMG_H

typedef struct s_img
{
	void	*_img;
	char	*_addr;
	int		_bits_per_pixel;
	int		_line_length;
	int		_endian;
}				t_img;

t_img	*img_init(void *mlx, int height, int width);
void	img_pixel_put(t_img *data, int x, int y, int color);
void	img_destruct(void *mlx, t_img *data);

#endif /* IMG_H */
