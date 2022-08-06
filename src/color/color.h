#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

int		convert_color(t_color c);
t_color	color_add_color(t_color a, t_color b);
t_color	color_add_num(t_color a, double num);
t_color	color_mult_color(t_color a, t_color b);
t_color	color_mult_num(t_color a, double num);
t_color	color_normalize(t_color a);

#endif
