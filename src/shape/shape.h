#ifndef SHAPE_H
#define SHAPE_H

#include "../minirt.h"

typedef enum e_shape_type
{
	SP,
}			t_shape_type;

typedef struct s_rad
{
	t_color	amb;
	t_color	dif;
	t_color	spec;
}	t_rad;

typedef struct s_shape
{
	struct s_shape	*next;
	t_shape_type	type;
	t_rad			coef;
	double			shineness;
}	t_shape;

#endif /* SHAPE_H */
