/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_easy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:42:12 by tsudo             #+#    #+#             */
/*   Updated: 2022/01/07 23:44:55 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_mem.h"
#include <stdlib.h>
#include <unistd.h>

static char	*gnl_easy_loop(int fd, char *buf, size_t bufsize)
{
	size_t	idx;
	ssize_t	ret;

	idx = 0;
	while (1)
	{
		if (idx >= bufsize)
		{
			buf = ft_realloc(buf, bufsize, bufsize * 2);
			if (buf == NULL)
				return (NULL);
			bufsize *= 2;
		}
		if (idx != 0 && buf[idx - 1] == '\n')
			ret = 0;
		else
			ret = read(fd, buf + idx, 1);
		if (ret <= 0)
			buf[idx] = '\0';
		if (buf[idx] == '\0')
			return (buf);
		idx++;
	}
}

char	*get_next_line_easy(int fd)
{
	char	tmp;
	char	*buf;

	if (read(fd, &tmp, 0) < 0)
		return (NULL);
	buf = malloc(16);
	if (buf == NULL)
		return (buf);
	buf = gnl_easy_loop(fd, buf, 16);
	if (buf != NULL && buf[0] == '\0')
		ft_free_set((void **)&buf, NULL);
	return (buf);
}
