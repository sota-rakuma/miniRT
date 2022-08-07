/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:42:13 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/07 17:40:34 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "../libft/libft.h"

double	double_max(double a, double b);
double	double_min(double a, double b);
void	ft_printf_and_exit(int status, char *format, ...);
long	strs_len(char **strs);
void	*ft_xalloc(size_t count, size_t size, const char *func_name);
void	free_all(char **strs);
void	usage(void);

#endif
