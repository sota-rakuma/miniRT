#include "minirt.h"

void	put_color_to_image(t_display *display, t_world *world)
{
	long	y;
	long	x;
	t_vec3d	to_screen_y;
	t_vec3d	to_screen;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		to_screen_y = vec3d_add(
				world->camera->screen_start_pos,
				vec3d_mult(world->camera->screen_vertical_normal,
					world->camera->dy * (double)y));
		x = 0;
		while (x < WIDTH)
		{
			to_screen = vec3d_add(to_screen_y,
					vec3d_mult(world->camera->screen_horizon_normal,
						world->camera->dx * (double)x));
			color = compute_color_of_pixel(world, to_screen);
			img_pixel_put(display->_img, x, y, convert_color(color));
			x++;
		}
		y++;
	}
}

int	draw(void *param)
{
	t_display	*display;

	display = (t_display *)param;
	mlx_put_image_to_window(
		display->_mlx, display->_win, display->_img->_img, 0, 0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all_info	all;

	if (argc != 2)
	{
		usage();
		exit(1);
	}
	all.world = world_init(argv[1]);
	camera_set(all.world->camera);
	all.display = display_init("miniRT");
	put_color_to_image(all.display, all.world);
	mlx_key_hook(all.display->_win, key_event, &all);
	mlx_hook(all.display->_win, X11_ON_DESTROY, X11_STRUCTURE_NOTIFY_MASK,
		click_cross_event, &all);
	mlx_loop_hook(all.display->_mlx, draw, all.display);
	mlx_loop(all.display->_mlx);
	return (0);
}
