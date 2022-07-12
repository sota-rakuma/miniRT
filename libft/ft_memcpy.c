/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 22:53:44 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:28:23 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;

	if (dst == 0 && src == 0)
		return (dst);
	s1 = (unsigned char *)dst;
	s2 = (const unsigned char *)src;
	while (n-- > 0)
		*s1++ = *s2++;
	return (dst);
}
