/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:19:26 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:29:07 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	int				diff;
	unsigned char	ch;

	if (!(ft_isascii(c)))
		return (c);
	ch = (unsigned char)c;
	diff = 'a' - 'A';
	if ('A' <= ch && ch <= 'Z')
		return (c + diff);
	return (c);
}
