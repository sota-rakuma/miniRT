/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 00:03:14 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/27 23:57:20 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	*str;
	int		count;

	if (s[0] == '\0')
		return (0);
	if (c == '\0')
		return (1);
	count = 0;
	str = (char *)s;
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (0 < i && (s[i] == c || str[i] == '\0') && s[i - 1] != c)
			count++;
		i++;
	}
	return (count);
}

static char	**ft_mem_alloc(char const *s, char c)
{
	int	wc;

	if (s == 0)
		return (0);
	wc = ft_word_count(s, c);
	return ((char **)ft_calloc((size_t)wc + 1, sizeof(char *)));
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

static void	*ft_free_all(char **s, int j)
{
	while (j-- > 0)
		free(s[j]);
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		first;
	int		last;
	int		j;

	arr = ft_mem_alloc(s, c);
	if (s == 0 || arr == 0)
		return (0);
	first = 0;
	last = -1;
	j = -1;
	while (++last < (int)ft_strlen(s) + 1)
	{
		if (s[last] == c || s[last] == '\0')
		{
			if (0 < last && s[last - 1] != c)
			{
				arr[++j] = ft_strdup_len(&s[first], (size_t)(last - first));
				if (arr[j] == 0)
					return (ft_free_all(arr, j));
			}
			first = last + 1;
		}
	}
	return (arr);
}
