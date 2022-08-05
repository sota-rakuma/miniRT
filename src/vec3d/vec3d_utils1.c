/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:36:03 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 18:39:48 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	vec3d_length(t_vec3d a)
{
	return (sqrt(vec3d_dot(a, a)));
}

t_vec3d	vec3d_unit(t_vec3d a)
{
	return (vec3d_mult(a, 1.0 / vec3d_length(a)));
}
