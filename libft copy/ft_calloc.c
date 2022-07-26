/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:03:36 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:27:48 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	ptr = malloc(size * count);
	if (ptr == 0)
		return (0);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
