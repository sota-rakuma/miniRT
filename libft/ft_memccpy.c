/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:24:55 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:28:08 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	ch;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	ch = (unsigned char)c;
	while (n-- > 0)
	{
		*s1 = *s2;
		dst++;
		if (*s2 == ch)
			return (dst);
		s1++;
		s2++;
	}
	return (0);
}
