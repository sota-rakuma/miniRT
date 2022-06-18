#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
	private:
		int	_trgb;
	public:
		Color(void);
		Color(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
		Color(const Color& another);
		~Color(void);
		Color&			operator=(const Color& another);
		unsigned char	getTransparency(void);
		unsigned char	getRed(void);
		unsigned char	getGreen(void);
		unsigned char	getBlue(void);
		void			setTransparency(unsigned char t);
		void			setRed(unsigned char r);
		void			setGreen(unsigned char g);
		void			setBlue(unsigned char b);
		int				getOpposite(void);
		void			addShade(double distance);
};


#endif /* COLOR_HPP */
