#include <cstring>
#include <exception>
#include <cstdlib>
#include <iostream>
#include "Win.hpp"
#ifdef __cplusplus
	extern "C"{
#endif
#include <mlx.h>
#ifdef __cplusplus
	}
#endif

#include <iostream>
Win::Win(void)
{
	_mlx = mlx_init();
	if (_mlx == NULL)
	{
		std::cerr << "mlx_init error" << std::endl;
		std::exit(1);
	}
	_win = mlx_new_window(_mlx, WIDTH, HEIGHT, const_cast<char *>(std::string("HelloWorld").c_str()));
	if (_win == NULL)
	{
		std::cerr << "mlx_new_window error" << std::endl;
		mlx_destroy_display(_mlx);
		free(_mlx);
		std::exit(1);
	}
}

Win::Win(const std::string& title)
{
	_mlx = mlx_init();
	if (_mlx == NULL)
	{
		std::cerr << "mlx_init error" << std::endl;
		std::exit(1);
	}
	_win = mlx_new_window(_mlx, WIDTH, HEIGHT, const_cast<char *>(title.c_str()));
	if (_win == NULL)
	{
		std::cerr << "mlx_new_window error" << std::endl;
		mlx_destroy_display(_mlx);
		free(_mlx);
		std::exit(1);
	}
}

Win::~Win()
{
	mlx_destroy_window(_mlx, _win);
	mlx_destroy_display(_mlx);
	free(_mlx);
}

void	*Win::getMlx(void) const
{
	return (_mlx);
}

void	*Win::getWin(void) const
{
	return (_win);
}

int	Win::putImage(t_data *data, int x, int y)
{
	std::cout << "a" << std::endl;
	int i = mlx_put_image_to_window(_mlx, _win, data->img, x, y);
	std::cout << "b" << std::endl;
	return (i);
}