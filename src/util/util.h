/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:42:13 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/09 00:02:56 by srakuma          ###   ########.fr       */
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
void	error(char *str);
void	error_line_msg(long line, char *msg);
long	strs_len(char **strs);
void	*ft_xalloc(size_t count, size_t size, const char *func_name);
void	free_all(char **strs);
void	usage(void);

#endif
