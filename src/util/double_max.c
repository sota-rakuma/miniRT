/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:41:48 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/04 10:41:54 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

double	double_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
