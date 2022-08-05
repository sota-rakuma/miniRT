/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:34:53 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 18:36:00 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	vec3d_dot(t_vec3d a, t_vec3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3d	vec3d_cross(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

t_vec3d	vec3d_sub(t_vec3d a, t_vec3d b)
{
	t_vec3d	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec3d	vec3d_add(t_vec3d a, t_vec3d b)
{
	t_vec3d	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec3d	vec3d_mult(t_vec3d a, double n)
{
	return ((t_vec3d){a.x * n, a.y * n, a.z * n});
}
