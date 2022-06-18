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
	_win = mlx_new_window(GraphicSystem::getMlx(), WIDTH, HEIGHT, const_cast<char *>(std::string("HelloWorld").c_str()));
	if (_win == NULL)
	{
		std::cerr << "mlx_new_window error" << std::endl;
		mlx_destroy_display(GraphicSystem::getMlx());
		free(GraphicSystem::getMlx());
		std::exit(1);
	}
}

Win::Win(const std::string& title)
{
	_win = mlx_new_window(GraphicSystem::getMlx(), WIDTH, HEIGHT, const_cast<char *>(title.c_str()));
	if (_win == NULL)
	{
		std::cerr << "mlx_new_window error" << std::endl;
		mlx_destroy_display(GraphicSystem::getMlx());
		free(GraphicSystem::getMlx());
		std::exit(1);
	}
}

Win::~Win()
{
	mlx_destroy_window(GraphicSystem::getMlx(), _win);
}

void	*Win::getWin(void) const
{
	return (_win);
}

int	Win::putImage(ImageData &data, int x, int y)
{
	return (mlx_put_image_to_window(GraphicSystem::getMlx(), _win, data.getImage(), x, y));
}
