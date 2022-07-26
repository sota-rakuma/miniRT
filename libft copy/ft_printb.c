/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 02:18:24 by srakuma           #+#    #+#             */
/*   Updated: 2022/06/28 01:25:00 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printb(void *ptr, size_t size)
{
	unsigned char	*mem;
	char			buf[9];
	size_t			n;

	mem = (unsigned char *)ptr;
	buf[8] = ' ';
	while (size--)
	{
		ft_memset(buf, '\0', 8);
		n = 8;
		while (n--)
			buf[8 - (n + 1)] = ((*mem >> n) & 1) + '0';
		if (!size)
			buf[8] = '\n';
		write(1, buf, 9);
		mem++;
	}
}
