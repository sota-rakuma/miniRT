/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 02:02:45 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/13 02:43:39 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>

#define BUFFER_SIZE 1
#define FD_MAX 256

static char	*x_strjoin_with_free(char *s1, bool b1, char *s2, bool b2)
{
	char	*str;

	str = ft_strjoin_with_free(s1, b1, s2, b2);
	if (str == NULL)
	{
		perror("malloc");
		exit(1);
	}
	return (str);
}

static char	*_read_line(int fd)
{
	char	*line;
	char	buf[BUFFER_SIZE + 1];
	ssize_t	read_byte;

	line = NULL;
	while (line == NULL || ft_strchr(line, '\n') == NULL)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte < 0)
		{
			perror("read");
			exit(1);
		}
		if (read_byte == 0)
			break ;
		buf[read_byte] = '\0';
		line = x_strjoin_with_free(line, true, buf, false);
	}
	return (line);
}

static char	*_get_line(int fd)
{
	static char	*save[FD_MAX] = {};
	char		*line;
	char		*at_newline;

	if (save[fd] == NULL || ft_strchr(save[fd], '\n') == NULL)
		save[fd] = x_strjoin_with_free(save[fd], true, _read_line(fd), true);
	line = save[fd];
	save[fd] = NULL;
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	at_newline = ft_strchr(line, '\n');
	if (at_newline)
	{
		if (at_newline[1] != '\0')
			save[fd] = x_strjoin_with_free(
					at_newline + 1, false, NULL, false);
		at_newline[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || FD_MAX <= fd || BUFFER_SIZE < 1)
		return (NULL);
	line = _get_line(fd);
	return (line);
}
