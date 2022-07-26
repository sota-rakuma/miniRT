/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:10:54 by srakuma           #+#    #+#             */
/*   Updated: 2021/10/02 19:07:48 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	return (0);
}
