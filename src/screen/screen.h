#ifndef SCREEN_H
#define SCREEN_H

#include "../img.h"

typedef struct s_screen
{
	void	*_mlx;
	void	*_win;
	t_img	*_img;
}				t_screen;

void	*win_init(void *mlx, char *title);
t_screen	*screen_init();
void		screen_destruct(t_screen *screen);

#endif /* SCREEN_H */
