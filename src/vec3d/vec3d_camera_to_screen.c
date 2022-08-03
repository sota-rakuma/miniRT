/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_camera_to_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 01:55:55 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/04 01:57:30 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec3d	vec3d_camera_to_screen(t_camera *camera, t_vec3d to_screen)
{
	return (vec3d_sub(to_screen, camera->pos));
}
