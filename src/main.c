#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	ft_printb(void *ptr, size_t size)
{
	unsigned char	*mem;
	char			buf[9];
	size_t			n;

	mem = (unsigned char *)ptr;
	buf[8] = ' ';
	while (size--)
	{
		memset(buf, '\0', 8);
		n = 8;
		while (n--)
			buf[8 - (n + 1)] = ((*mem >> n) & 1) + '0';
		if (!size)
			buf[8] = '\n';
		write(1, buf, 9);
		mem++;
	}
}

#include <mlx.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	aclose(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, aclose, &vars);
	mlx_loop(vars.mlx);
}