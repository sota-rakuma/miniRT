/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_normal_vec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:43:27 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/04 10:43:57 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec3d	shape_normal_vec(t_shape *shape, t_vec3d pos)
{
	t_vec3d	normal;

	if (shape->kind == SPHERE)
		normal = vec3d_sub(pos, shape->center);
	else if (shape->kind == PLANE)
		normal = shape->oriental_normal;
	else if (shape->kind == CYLINDER)
	{
		normal = vec3d_cross(vec3d_sub(pos, shape->center),
				shape->oriental_normal);
		normal = vec3d_cross(shape->oriental_normal, normal);
	}
	return (vec3d_unit(normal));
}
