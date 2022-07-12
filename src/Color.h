#ifndef COLOR_H
#define COLOR_H

typedef int	t_color;

t_color	create_color(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char get_transparency(t_color trgb);
unsigned char get_red(t_color trgb);
unsigned char get_green(t_color trgb);
unsigned char get_blue(t_color trgb);
t_color set_transparency(unsigned char t, t_color trgb);
t_color set_red(unsigned char r, t_color trgb);
t_color set_green(unsigned char g, t_color trgb);
t_color set_blue(unsigned char b, t_color trgb);
t_color get_opposite(t_color trgb);
t_color add_shade(double distance, t_color trgb);

#endif /* COLOR_H */
