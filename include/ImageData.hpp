#ifndef IMAGEDATA_HPP
#define IMAGEDATA_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include <mlx.h>
#ifdef __cplusplus
}
#endif

#include "GraphicSystem.hpp"

#define WIDTH 500
#define HEIGHT 500

class ImageData {
  private:
	// GraphicSystem	_mlx;
	void* _img;
	char* _addr;
	int _bits_per_pixel;
	int _line_length;
	int _endian;

  public:
	ImageData(void);
	~ImageData(void);
	void* getImage(void);
	void* getAddress(void);
	int getBPP(void);
	int getLineLen(void);
	int getEndian(void);
};

#endif /* IMAGEDATA_HPP */
