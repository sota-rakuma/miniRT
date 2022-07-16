#include "../minirt.h"

void *win_init(void *mlx, char *title)
{
	void *win;

	win = mlx_new_window(mlx, WIDTH, HEIGHT, title);
	if (win == NULL)
	{
		printf("failed to make new window\n");
		mlx_destroy_display(mlx);
		free(mlx);
		exit(1);
	}
	return (win);
}

t_screen	*screen_init(char *title)
{
	t_screen	*screen;

	screen = (t_screen *)malloc(sizeof(t_screen));
	if (screen == NULL)
	{
		printf("failed to malloc screen\n");
		exit(1);
	}
	screen->_mlx = mlx_init();
	if (screen->_mlx == NULL)
	{
		printf("falied to init mlx\n");
		exit(0);
	}
	screen->_win = win_init(screen->_mlx, title);
	screen->_img = img_init(screen->_mlx, WIDTH, HEIGHT);
	return (screen);
}

void	screen_destruct(t_screen *screen)
{
	img_destruct(screen->_mlx, screen->_img);
	mlx_destroy_window(screen->_mlx, screen->_win);
	mlx_destroy_display(screen->_mlx);
	free(screen->_mlx);
	free(screen);
}