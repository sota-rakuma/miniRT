#include <mlx.h>


int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "hello world");
	mlx_loop(mlx);
	(void)mlx_win;
	return (0);
}
