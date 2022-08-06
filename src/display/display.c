#include "../minirt.h"

void	*win_init(void *mlx, char *title)
{
	void	*win;

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

t_display	*display_init(char *title)
{
	t_display	*display;

	display = (t_display *)malloc(sizeof(t_display));
	if (display == NULL)
	{
		printf("failed to malloc screen\n");
		exit(1);
	}
	display->_mlx = mlx_init();
	if (display->_mlx == NULL)
	{
		printf("falied to init mlx\n");
		exit(0);
	}
	display->_win = win_init(display->_mlx, title);
	display->_img = img_init(display->_mlx, HEIGHT, WIDTH);
	return (display);
}

void	display_destruct(t_display *display)
{
	img_destruct(display->_mlx, display->_img);
	mlx_destroy_window(display->_mlx, display->_win);
	mlx_destroy_display(display->_mlx);
	free(display->_mlx);
	free(display);
}
