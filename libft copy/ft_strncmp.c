/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:27:53 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:28:58 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ch1;
	unsigned char	*ch2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	while (!(ch1[i] == '\0' && ch2[i] == '\0') && i < n - 1)
	{
		if ((ch1[i] != ch2[i]))
			return (ch1[i] - ch2[i]);
		i++;
	}
	return (ch1[i] - ch2[i]);
}
