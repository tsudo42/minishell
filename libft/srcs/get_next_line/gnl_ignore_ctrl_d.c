/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_ignore_ctrl_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/30 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_mem.h"
#include <stdlib.h>
#include <unistd.h>

static char	*gnl_ignore_ctrl_d_helper(int fd, char *buf, size_t bufsize)
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
			ret = -1;
		else
			ret = read(fd, buf + idx, 1);
		if (ret < 0)
			buf[idx] = '\0';
		if (ret != 0 && buf[idx] == '\0')
			return (buf);
		idx += ret;
	}
}

char	*gnl_ignore_ctrl_d(int fd)
{
	char	tmp;
	char	*buf;

	if (read(fd, &tmp, 0) < 0)
		return (NULL);
	buf = malloc(16);
	if (buf == NULL)
		return (buf);
	buf = gnl_ignore_ctrl_d_helper(fd, buf, 16);
	if (buf != NULL && buf[0] == '\0')
		ft_free_set((void **)&buf, NULL);
	return (buf);
}
