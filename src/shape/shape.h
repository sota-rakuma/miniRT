/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:44:17 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/04 10:44:28 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "../minirt.h"

double	with_sphere(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double	with_plane(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double	with_cylinder(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);
double	shape_get_intersection(t_vec3d o_to_screen, t_vec3d o, t_shape *shape);

t_vec3d	shape_normal_vec(t_shape *shape, t_vec3d pos);

#endif /* SHAPE_H */
