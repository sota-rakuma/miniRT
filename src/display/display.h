#ifndef SCREEN_H
#define SCREEN_H

#include "../img.h"

typedef struct s_display
{
	void	*_mlx;
	void	*_win;
	t_img	*_img;
}				t_display;

void		*win_init(void *mlx, char *title);
t_display	*display_init();
void		display_destruct(t_display *display);

#endif /* SCREEN_H */
