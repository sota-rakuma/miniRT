/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:42:32 by srakuma           #+#    #+#             */
/*   Updated: 2022/06/27 00:27:43 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Color.h"

t_color	create_color(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(t_color*)(unsigned char[4]){b, g, r, t});
}
unsigned char get_transparency(t_color trgb)
{
	return (((unsigned char*)&trgb)[3]);
}

unsigned char get_red(t_color trgb)
{
	return (((unsigned char*)&trgb)[2]);
}

unsigned char get_green(t_color trgb)
{
	return (((unsigned char*)&trgb)[1]);
}

unsigned char get_blue(t_color trgb)
{
	return (((unsigned char*)&trgb)[0]);
}

t_color set_transparency(unsigned char t, t_color trgb)
{
	((unsigned char*)&trgb)[3] = t;
	return (trgb);
}

t_color set_red(unsigned char r, t_color trgb)
{
	((unsigned char*)&trgb)[2] = r;
	return (trgb);
}

t_color set_green(unsigned char g, t_color trgb)
{
	((unsigned char*)&trgb)[1] = g;
	return (trgb);
}

t_color set_blue(unsigned char b, t_color trgb)
{
	((unsigned char*)&trgb)[0] = b;
	return (trgb);
}

t_color get_opposite(t_color trgb)
{
	return (~trgb);
}

t_color add_shade(double distance, t_color trgb)
{
	((unsigned char*)&trgb)[0] = (unsigned char)(0xff * distance);
	return (trgb);
}
