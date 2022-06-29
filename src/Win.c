#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include "Win.h"
#include "ImageData.h"

void	*init_win(void *mlx, char *title)
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

void	destruct_win(void *mlx, void *win)
{
	mlx_destroy_window(mlx, win);
}