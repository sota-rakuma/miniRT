#include "ForMapping.h"
#include <stdio.h>

t_for_map *init_data_for_mapping(void *mlx, void *win)
{
	t_for_map *new;

	new = (t_for_map *)malloc(sizeof(t_for_map));
	if (new == NULL)
	{
		printf("failed to malloc frame sturcture\n");
		exit(1);
	}
	new->_mlx = mlx;
	new->_win = win;
	return (new);
}

void destruct_data_for_mapping(t_for_map *data)
{
	mlx_clear_window(data->_mlx, data->_win);
	mlx_destroy_window(data->_mlx, data->_win);
	mlx_destroy_display(data->_mlx);
	free(data);
}
