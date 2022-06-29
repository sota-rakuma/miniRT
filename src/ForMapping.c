#include "ForMapping.h"
#include <stdio.h>

t_for_map	*init_data_for_mapping(void *mlx, void *win)
{
	t_for_map	*new;

	new = (t_for_map *)malloc(sizeof(t_for_map));
	if (new == NULL)
	{
		printf("failed to malloc frame sturcture\n");
		exit(1);
	}
	new->_mlx = mlx;
	new->_win = win;
	new->_frame_list = NULL;
	return (new);
}

/**
 * @brief if failed to malloc new list, then return 1, else 0
 *
 * @param t_for_map it is composed of mlx, t_win and list of t_frame
 * @param t_frame the compoenet added last
 * @return int
**/
int	add_frame(t_for_map *data, t_frame *frame)
{
	t_list	*new;

	new = ft_lstnew(frame);
	if (new == NULL)
		return (1);
	ft_lstadd_back(&(data->_frame_list), new);
	return (0);
}

int		draw_frame(void *mlx, void *win, t_frame *frame)
{
	return (mlx_put_image_to_window(mlx, win, frame->_img->_img, \
										frame->_start_x, frame->_start_y));
}

int	get_animation(t_for_map *data)
{
	t_list	*now = data->_frame_list;

	while (now)
	{
		draw_frame(data->_mlx, data->_win, (t_frame *)(now->content));
		now = now->next;
	}
	return (0);
}

void	destruct_data_for_mapping(t_for_map *data)
{
	ft_lstclear(&data->_frame_list, data->_mlx, destruct_frame);
	mlx_clear_window(data->_mlx, data->_win);
	mlx_destroy_window(data->_mlx, data->_win);
	mlx_destroy_display(data->_mlx);
	free(data);
}
