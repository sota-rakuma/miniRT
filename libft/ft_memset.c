/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:41:56 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:28:28 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	ch;
	unsigned char	*str;
	size_t			i;

	ch = (unsigned char)c;
	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = ch;
		i++;
	}
	return (b);
}
