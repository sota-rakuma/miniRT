/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:45:48 by srakuma           #+#    #+#             */
/*   Updated: 2022/07/13 02:05:54 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_with_free(char *s1, bool b1, char *s2, bool b2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (b1)
		free(s1);
	if (b2)
		free(s2);
	return (str);
}
