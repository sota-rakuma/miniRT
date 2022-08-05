/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:58:51 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/04 10:59:31 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	convert_color(t_color c)
{
	return ((int)c.r << 16 | (int)c.g << 8 | (int)c.b);
}

t_color	color_add_color(t_color	a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color	color_add_num(t_color a, double num)
{
	return ((t_color){a.r + num, a.g + num, a.b + num});
}

t_color	color_mult_color(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color	color_mult_num(t_color a, double num)
{
	return ((t_color){a.r * num, a.g * num, a.b * num});
}

t_color	color_normalize(t_color a)
{
	return ((t_color){
		double_max(0.0, double_min(1.0, a.r)),
		double_max(0.0, double_min(1.0, a.g)),
		double_max(0.0, double_min(1.0, a.b))});
}
