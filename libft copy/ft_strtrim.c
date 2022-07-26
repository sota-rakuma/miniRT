/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:05:58 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/27 23:41:09 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_set_check(char c, char *set)
{
	if (set == 0)
		return (0);
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_search_str(char *s, char *set)
{
	size_t	len;
	size_t	tmp;

	len = 0;
	while (s[len])
	{
		tmp = 0;
		while (ft_set_check(s[len + tmp], set))
			tmp++;
		if (s[len + tmp] == '\0')
			return (len);
		if (tmp > 0)
			len += tmp;
		len++;
	}
	return (len);
}

static char	*ft_strdup_len(const char *s1, size_t len)
{
	char	*str;

	if (s1 == 0)
		return (0);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	char		*ptr_to_s1;
	char		*ptr_to_set;
	size_t		len;
	size_t		i;

	if (s1 == 0)
		return (0);
	ptr_to_s1 = (char *)s1;
	ptr_to_set = (char *)set;
	i = 0;
	while (ft_set_check(ptr_to_s1[i], ptr_to_set))
		i++;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	len = ft_search_str(&ptr_to_s1[i], ptr_to_set);
	str = ft_strdup_len(&ptr_to_s1[i], len);
	return (str);
}
