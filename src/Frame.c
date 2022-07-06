#include "Frame.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief
 *
 * @param imt	pointer to image data
 * @param start		the point of start of window which is drawn image.
 * image is bigger than window and you want to draw part of image into window,
 *  x and y can be negative value (it may be the negative value of the top left vertext(x, y) of the part of image which is you wanna see)
 * @return t_frame*
 */
t_frame	*init_frame(t_image_data *img, t_coordinate start)
{
	t_frame	*new;

	new = (t_frame *)malloc(sizeof(t_frame));
	if (new == NULL)
	{
		printf("failed to malloc frame sturcture\n");
		exit(1);
	}
	new->_img = img;
	new->_start_x = start.x;
	new->_start_y = start.y;
	return (new);
}

void	*destruct_frame(void *mlx, t_frame *frame)
{
	destruct_image_data(mlx, frame->_img);
	free(frame);
}