/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:50:34 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:28:25 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (s1 == 0 && s2 == 0)
		return (dst);
	if (s1 > s2)
	{
		s1 += len - 1;
		s2 += len - 1;
		while (len-- > 0)
			*s1-- = *s2--;
	}
	else if (s1 < s2)
	{
		while (len-- > 0)
			*s1++ = *s2++;
	}
	return (dst);
}
