/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:03:52 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:29:10 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	int				diff;
	unsigned char	ch;

	if (!(ft_isascii(c)))
		return (c);
	ch = (unsigned char)c;
	diff = 'a' - 'A';
	if ('a' <= ch && ch <= 'z')
		return (c - diff);
	return (c);
}
