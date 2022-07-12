/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:55:05 by srakuma           #+#    #+#             */
/*   Updated: 2022/06/27 22:09:57 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void *ele, void (*del)())
{
	if (ele)
		del(ele, lst->content);
	else
		del(lst->content);
	lst->content = NULL;
	free(lst);
	lst = 0;
}
