/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:29:00 by srakuma           #+#    #+#             */
/*   Updated: 2022/06/27 01:54:57 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(int n)
{
	int	cnt;

	cnt = 1;
	if (n == 0)
		return (cnt + 1);
	if (n < 0)
		cnt++;
	while (n)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

static void	substitute(int n, int digit, char *str)
{
	if (n == INT_MIN)
	{
		str[0] = '-';
		str[1] = '2';
		substitute(147483648, digit, str);
	}
	else if (n < 0)
	{
		str[0] = '-';
		substitute(n * (-1), digit, str);
	}
	else
	{
		if (n / 10)
			substitute(n / 10, digit - 1, str);
		str[digit - 2] = (char)((n % 10) + '0');
	}
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*str;

	digit = ft_count_digit(n);
	str = (char *)ft_calloc(digit, sizeof(char));
	if (str == 0)
		return (0);
	substitute(n, digit, str);
	return (str);
}
