/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 20:12:13 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/27 23:36:37 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	char	ch;

	i = (int)ft_strlen(s);
	ptr = (char *)s;
	ch = (char)c;
	while (0 <= i)
	{
		if (*(ptr + i) == ch)
			return ((char *)ptr + i);
		i--;
	}
	return (0);
}
