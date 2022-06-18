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

const void *GraphicSystem::_mlx = mlx_init();

void	my_mlx_pixel_put(ImageData &data, int x, int y, int color)
{
	char	*dst;

	dst = ((char *)data.getAddress()) + (y * data.getLineLen() + x * (data.getBPP() / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(ImageData &img, size_t height, size_t width, size_t x, size_t y)
{
	size_t	area = height * width;
	for (size_t i = 0; i < area; i++)
	{
		my_mlx_pixel_put(img, i % height + x, i / height + y, 0x00ff0000);
	}
}

void	draw_circle(ImageData &img, size_t radius, size_t a, size_t b)
{
	for (size_t i = 0; i < HEIGHT * WIDTH; i+=1)
	{
		size_t	x = i % HEIGHT;
		size_t	y = i / HEIGHT;
		if ((x - a) * (x - a) + (y - b) * (y - b) == radius * radius)
			my_mlx_pixel_put(img, x, y, 0x00ff0000);
	}
}

void	draw_orthodox_triangle(ImageData &img, int width, int height)
{
	for (size_t i = 0; i < width / 2; i++)
	{
	}
}

int	main(void)
{
	Win			vars;
	ImageData	img;

	my_mlx_pixel_put(img, 5, 5, 0x00FF0000);
	draw_square(img, HEIGHT / 5, WIDTH / 5, 0, 0);
	draw_circle(img, 100, HEIGHT / 2, WIDTH / 2);

	vars.putImage(img, 0, 0);
	mlx_key_hook(vars.getWin(), Hook::close, &vars);
	mlx_destroy_hook(vars.getWin(), Hook::close, &vars);
	mlx_loop(GraphicSystem::getMlx());
	return (0);
}
