#include "mlx_int.h"

int mlx_destroy_hook(t_win_list *win, int (*funct)(void *),void *param)
{
  win->hooks[DestroyNotify].hook = funct;
  win->hooks[DestroyNotify].param = param;
  win->hooks[DestroyNotify].mask = StructureNotifyMask;
}
