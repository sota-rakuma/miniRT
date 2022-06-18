#include <iostream>
#include <string>
#include <cmath>
#include "Hook.hpp"
#include "Win.hpp"

#ifdef __cplusplus
	extern "C"{
#endif
#include <mlx.h>
#ifdef __cplusplus
	}
#endif

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_data *img, size_t height, size_t width, size_t x, size_t y)
{
	size_t	area = height * width;
	for (size_t i = 0; i < area; i++)
	{
		my_mlx_pixel_put(img, i % height + x, i / height + y, 0x00ff0000);
	}
}

void	draw_circle(t_data *img, size_t radius, size_t a, size_t b)
{
	for (size_t i = 0; i < HEIGHT * WIDTH; i+=1)
	{
		size_t	x = i % HEIGHT;
		size_t	y = i / HEIGHT;
		if ((x - a) * (x - a) + (y - b) * (y - b) == radius * radius)
			my_mlx_pixel_put(img, x, y, 0x00ff0000);
	}
}

void	draw_orthodox_triangle(t_data *img, int width, int height)
{
	for (size_t i = 0; i < width / 2; i++)
	{
	}
}

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	main(void)
{
	Win			vars;
	t_data		img;

	img.img = mlx_new_image(vars.getMlx(), WIDTH, HEIGHT);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	draw_square(&img, HEIGHT / 5, WIDTH / 5, 0, 0);
	draw_circle(&img, 100, HEIGHT / 2, WIDTH / 2);

	vars.putImage(&img, 0, 0);
	mlx_key_hook(vars.getWin(), Hook::close, &vars);
	mlx_destroy_hook(vars.getWin(), Hook::close, &vars);
	mlx_loop(vars.getMlx());

	return (0);
}
