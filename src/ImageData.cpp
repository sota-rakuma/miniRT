#include "ImageData.hpp"
#include <iostream>
#include <cstdlib>

ImageData::ImageData(void)
{
	_img = mlx_new_image(GraphicSystem::getMlx(), WIDTH, HEIGHT);
	if (_img == NULL)
	{
		std::cerr << "faild to make new image" << std::endl;
		std::exit(1);
	}
	_addr = mlx_get_data_addr(_img, &_bits_per_pixel, &_line_length, &_endian);
}

ImageData::~ImageData(void)
{

}

void	*ImageData::getImage(void)
{
	return (_img);
}

void	*ImageData::getAddress(void)
{
	return (_addr);
}

int	ImageData::getBPP(void)
{
	return (_bits_per_pixel);
}

int	ImageData::getLineLen(void)
{
	return (_line_length);
}

int	ImageData::getEndian(void)
{

	return (_endian);
}
