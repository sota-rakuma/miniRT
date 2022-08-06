#include "../minirt.h"

t_color	color_normalize(t_color a)
{
	return ((t_color){
		double_max(0.0, double_min(1.0, a.r)),
		double_max(0.0, double_min(1.0, a.g)),
		double_max(0.0, double_min(1.0, a.b))});
}
