#include <stdio.h>
#include <math.h>
#include "Win.h"
#include "ForMapping.h"
#include "Color.h"

void	create_clip(t_for_map *data, int height, int width, int x, int y)
{
	int	flag = 1;
	int	color = 0x00ff0100;
	while (color != 0x00ff0000)
	{
		t_image_data	*img_dat = init_image_data(data->_mlx, height, width);
		t_frame			*frame = init_frame(img_dat, x, y);

		create_square((t_image_data *)(frame->_img), height, width, color);
 		if (add_frame(data, frame))
			exit(1);

		int	bit_move = ((2 - flag) < 0 ? -(2 - flag) : (2 - flag)) * 8;
		if ((unsigned char)(color >> bit_move) == 0xff)
		{
			int	previous = 2 - (flag >> 1);
			unsigned char	tmp = (color >> (previous * 8));
			tmp--;
			((unsigned char *)&color)[previous] = tmp;
			if ((unsigned char)(color >> (previous * 8)) == 0)
			{
				if (flag == 4)
					flag = 1;
				else
					flag<<=1;
			}
		}
		else
		{
			unsigned char	tmp = (color >> bit_move);
			tmp++;
			int	index = (2 - flag) < 0 ? -(2 - flag) : (2 - flag);
			((unsigned char *)&color)[index] = tmp;
		}
	}
}

int	main(void)
{
	void	*mlx = mlx_init();
	if (mlx == NULL)
	{
		printf("initialized mlx error\n");
		exit(0);
	}
	void		*win = init_win(mlx, "hello world");
	t_for_map	*data = init_data_for_mapping(mlx, win);

	int	height = HEIGHT;
	int	width = WIDTH;

	for (size_t i = 0; i < HEIGHT / 2; i+=120)
	{
		create_clip(data, height, width, i, i);
		height -= 240;
		width -= 240;
	}

	mlx_loop_hook(mlx, get_animation, data);
	mlx_loop(mlx);
	return (0);
}