#ifndef WIN_HPP
#define WIN_HPP

#define HEIGHT 500
#define WIDTH 500

#include <string>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

class Win
{
private:
	void	*_mlx;
	void	*_win;
public:
	Win(void);
	Win(const std::string& title);
	~Win(void);
	void	*getMlx(void) const;
	void	*getWin(void) const;
	int	putImage(t_data *img, int x, int y);
};

#endif /* WIN_HPP */
