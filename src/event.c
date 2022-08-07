#include "minirt.h"

void	destruct_all(t_all_info *all)
{
	world_destuctor(all->world);
	display_destruct(all->display);
}

int	key_event(int key_code, void *param)
{
	printf("key_code: %d\n", key_code);
	if (key_code == 65307)
	{
		destruct_all(param);
		exit(0);
	}
	return (0);
}

int	click_cross_event(void *param)
{
	destruct_all(param);
	exit(0);
	return (0);
}
