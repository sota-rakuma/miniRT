#include "minirt.h"

int key_event(int key_code, void *param)
{
	printf("key_code: %d\n", key_code);
	if (key_code == 65307)
		exit(0);
	return (0);
}

int main(void)
{
	void *mlx = mlx_init();
	if (mlx == NULL)
	{
		printf("initialized mlx error\n");
		exit(0);
	}
	void *win = win_init(mlx, "hello world");

	int height = HEIGHT;
	int width = WIDTH;

	mlx_key_hook(win, key_event, NULL);
	mlx_loop(mlx);
	return (0);
}
