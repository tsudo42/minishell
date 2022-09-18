/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:42:12 by tsudo             #+#    #+#             */
/*   Updated: 2022/01/07 23:44:55 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_internal.h"
#include <ft_string.h>
#include <ft_mem.h>
#include <stdlib.h>
#include <unistd.h>

static char	*gnl_popall(t_gnl_buf *buf)
{
	char	*str;

	if (buf->size == 0)
		str = NULL;
	else
		str = ft_substr(buf->ptr, 0, buf->size);
	free(buf->ptr);
	buf->ptr = NULL;
	buf->size = 0;
	return (str);
}

static void	*gnl_popfront_helper(t_gnl_buf buf)
{
	unsigned char	*ptr_nl;
	unsigned char	*ptr_zero;

	if (buf.ptr == NULL || buf.size == 0)
		return (NULL);
	ptr_nl = ft_memchr(buf.ptr, '\n', buf.size);
	ptr_zero = ft_memchr(buf.ptr, '\0', buf.size);
	if (ptr_zero != NULL && ptr_zero != buf.ptr)
		ptr_zero--;
	if (ptr_nl == NULL || ptr_zero == NULL)
	{
		if (ptr_nl == NULL)
			return (ptr_zero);
		return (ptr_nl);
	}
	if (ptr_nl < ptr_zero)
		return (ptr_nl);
	return (ptr_zero);
}

static char	*gnl_popfront(t_gnl_buf *buf, int *error, int force)
{
	unsigned char	*ptr;
	size_t			len;
	char			*ret;

	ptr = gnl_popfront_helper(*buf);
	if (ptr == NULL)
	{
		if (force)
			return (gnl_popall(buf));
		return (NULL);
	}
	len = ptr - (unsigned char *)(buf->ptr) + 1;
	ret = ft_substr(buf->ptr, 0, len);
	if (ret == NULL)
		*error = 1;
	else
	{
		buf->size -= len;
		if (buf->size == 0)
			free(gnl_popall(buf));
		else
			buf->ptr = ft_memmove(buf->ptr, buf->ptr + len, buf->size);
	}
	return (ret);
}

static char	*gnl_read(t_gnl_buf *buf, int fd)
{
	char	*str;
	ssize_t	len;
	int		error;

	error = 0;
	str = gnl_popfront(buf, &error, 0);
	while (str == NULL && error == 0)
	{
		buf->ptr = ft_realloc(buf->ptr, buf->size, buf->size + BUFFER_SIZE);
		if (buf->ptr == NULL)
			break ;
		len = read(fd, buf->ptr + buf->size, BUFFER_SIZE);
		if (len < 0)
			break ;
		buf->size += len;
		if (len < BUFFER_SIZE)
			return (gnl_popfront(buf, &error, 1));
		str = gnl_popfront(buf, &error, 0);
	}
	if (str == NULL)
		free(gnl_popall(buf));
	return (str);
}

char	*get_next_line(int fd)
{
	static t_gnl_buf	gnl_buf[FD_MAX];
	char				tmp;

	if (read(fd, &tmp, 0) < 0)
		return (NULL);
	if (fd < 0 || FD_MAX <= fd)
		return (NULL);
	return (gnl_read(&(gnl_buf[fd]), fd));
}
