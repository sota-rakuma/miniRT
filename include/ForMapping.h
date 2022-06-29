#ifndef FORMAPPING_H
#define FORMAPPING_H

#include <mlx.h>
#include "Win.h"
#include "Frame.h"
#include "libft.h"

typedef struct s_for_map
{
	void	*_mlx;
	void	*_win;
	t_list	*_frame_list;
}				t_for_map;

t_for_map	*init_data_for_mapping(void *mlx, void *win);
int			add_frame(t_for_map *data, t_frame *frame);
int			get_animation(t_for_map *data);
void		destruct_data_for_mapping(t_for_map *data);

#endif /* FORMAPPING_H */
