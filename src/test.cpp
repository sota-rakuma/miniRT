#include <iostream>
#include <string>

#ifdef __cplusplus
	extern "C"{
#endif
#include <mlx.h>
#ifdef __cplusplus
	}
#endif

int	main(void)
{
	using namespace std;
	void	*mlx;
	void	*mlx_win;
	string	a("hello world");

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, const_cast<char *>(a.c_str()));
	mlx_loop(mlx);
	(void)mlx_win;
	return (0);
}
