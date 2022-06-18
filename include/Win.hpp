#ifndef WIN_HPP
#define WIN_HPP

#define HEIGHT 500
#define WIDTH 500

#include "GraphicSystem.hpp"
#include "ImageData.hpp"
#include <string>

class Win {
  private:
	// GraphicSystem	_mlx;
	void* _win;

  public:
	Win(void);
	Win(const std::string& title);
	~Win(void);
	void* getWin(void) const;
	int putImage(ImageData& img, int x, int y);
};

#endif /* WIN_HPP */
