/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:44:17 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/06 21:19:50 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "../color/color.h"
# include "../vec3d/vec3d.h"
#include "../util/util.h"
# include <stdbool.h>

// shape
typedef enum e_shape_kind {
	SPHERE,
	PLANE,
	CYLINDER,
} t_shape_kind;

typedef struct s_shape {
	struct s_shape	*next;
	t_shape_kind	kind;

	// common
	t_color			color;
	t_color			ka;
	t_color			kd;
	t_color			ks;
	double			shininess;

	// sphere
	t_vec3d			center;
	double			radius;

	// plane
	t_vec3d			normal;
	t_vec3d			point;
	bool			is_mirror;

	// cylinder
	// t_vec3d			center;
	// t_vec3d			normal;
	// double			radius;
	double				height;
} t_shape;

double	with_sphere(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double	with_plane(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double	with_cylinder(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double	shape_get_intersection(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);

t_vec3d	shape_normal_vec(t_shape *shape, t_vec3d pos);

#endif /* SHAPE_H */
