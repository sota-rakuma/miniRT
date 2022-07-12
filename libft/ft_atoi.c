/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:25:49 by srakuma           #+#    #+#             */
/*   Updated: 2021/04/24 12:27:41 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_ok(long int num, int c)
{
	long int	ov_div;
	long int	ov_mod;
	int			nxt;

	nxt = c - '0';
	ov_div = LONG_MAX / 10;
	ov_mod = LONG_MAX % 10;
	if ((ov_div < num) || (ov_div == num && ov_mod < nxt))
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (('\t' <= ch && ch <= '\r') || ch == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						minus;
	long int				tmp;

	i = 0;
	tmp = 0;
	minus = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		minus = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (is_ok(tmp, str[i]) && minus == 0)
			return (-1);
		else if (is_ok(tmp, str[i]) && minus == 1)
			return (0);
		tmp = 10 * tmp + (str[i] - '0');
		i++;
	}
	if (minus)
		tmp *= -1;
	return ((int)tmp);
}
