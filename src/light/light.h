#ifndef LIGHT_H
# define LIGHT_H

# include "../color/color.h"
# include "../vec3d/vec3d.h"

// light
typedef enum e_light_kind
{
	AMBIENT_LIGHT,
	LIGHT,
}	t_light_kind;

typedef struct s_light
{
	struct s_light	*next;
	t_light_kind	kind;

	double			intensity;
	t_color			color;
	t_vec3d			pos;
}				t_light;

#endif /* LIGHT_H */
