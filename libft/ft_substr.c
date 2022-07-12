/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:18:07 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/27 23:56:51 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (s == 0)
		return (0);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (0);
	ft_strlcpy(ptr, &s[start], len + 1);
	return (ptr);
}
