/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:36:19 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 18:40:02 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

typedef struct s_vec3d {
	double	x;
	double	y;
	double	z;
}	t_vec3d;

// vec3d_utils.c
double	vec3d_dot(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_cross(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_sub(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_add(t_vec3d a, t_vec3d b);
t_vec3d	vec3d_mult(t_vec3d a, double n);

// vec3d_utils1.c
double	vec3d_length(t_vec3d a);
t_vec3d	vec3d_unit(t_vec3d a);

#endif /* VEC3D_H */
