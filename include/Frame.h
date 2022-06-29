#ifndef FRAME_H
#define FRAME_H

#include <mlx.h>
#include "ImageData.h"
#include "libft.h"

typedef struct s_frame
{
	t_image_data	*_img;
	int				_start_x;
	int				_start_y;
}				t_frame;

t_frame	*init_frame(t_image_data *img, int x, int y);
void	*destruct_frame(void *mlx, t_frame *frame);

#endif /* FRAME_H */
