/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define TMPFILE_PREF ".minishell_heredoc_"
#define TMPFILE_BUFLEN 40

/**
 * This function tries to open heredoc.
 * idx will be used to generate a unique filename
 * even if multiple heredoc is necessary.
 */
static int	heredoc_tmpfile_open(int *idx, char *filename)
{
	int		try_count;
	int		fd;
	char	*filename_num;

	ft_strlcpy(filename, TMPFILE_PREF, TMPFILE_BUFLEN);
	filename_num = filename + ft_strlen(TMPFILE_PREF);
	try_count = 0;
	errno = EEXIST;
	while (errno == EEXIST && try_count < 10)
	{
		errno = 0;
		ft_itoa_buf(*idx, filename_num, 20);
		(*idx)++;
		fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
		try_count++;
	}
	if (fd < 0)
	{
		perror(EXEC_ERRMSG ": heredoc: open");
		if (fd >= 0)
			close(fd);
		return (-1);
	}
	return (fd);
}

static int	heredoc_write(int fd, const char *input)
{
	size_t		len;
	int			ret;

	len = ft_strlen(input);
	while (len > INT_MAX)
	{
		ret = write(fd, input, INT_MAX);
		if (ret < 0)
		{
			perror(EXEC_ERRMSG ": heredoc: write");
			return (-1);
		}
		input += ret;
		len -= ret;
	}
	if (write(fd, input, len) < 0)
	{
		perror(EXEC_ERRMSG ": heredoc: write");
		return (-1);
	}
	return (0);
}

static int	heredoc_tmpfile_terminate(int fd, const char *filename)
{
	int	ret;
	int	ret2;

	ret = 0;
	if (filename != NULL)
	{
		ret = unlink(filename);
		if (ret < 0)
			perror(EXEC_ERRMSG ": heredoc: unlink");
	}
	ret2 = 0;
	if (fd >= 0)
	{
		ret2 = close(fd);
		if (ret2 < 0)
			perror("close");
	}
	if (ret < 0 || ret2 < 0)
		return (-1);
	return (0);
}

static int	heredoc_tmpfile(char *input, int *idx)
{
	int		fd;
	int		fd2;
	char	filename[TMPFILE_BUFLEN];
	int		ret;

	fd = heredoc_tmpfile_open(idx, filename);
	if (fd < 0)
	{
		free(input);
		return (-1);
	}
	ret = -1;
	fd2 = open(filename, O_RDONLY, 0600);
	if (fd2 < 0)
		perror(EXEC_ERRMSG ": heredoc: open");
	else
		ret = heredoc_write(fd, input);
	free(input);
	if (heredoc_tmpfile_terminate(fd, filename) < 0 || ret < 0)
	{
		if (fd2 >= 0 && close(fd2) < 0)
			perror(EXEC_ERRMSG ": heredoc: close");
		return (-1);
	}
	return (fd2);
}

int	heredoc_set(char *delim, int *idx)
{
	int		fd;
	char	*input;
	int		is_error;

	is_error = 0;
	input = heredoc_input(delim, &is_error);
	if (is_error != 0)
	{
		free(input);
		return (-1);
	}
	if (input == NULL || ft_strlen(input) == 0)
	{
		free(input);
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			perror(EXEC_ERRMSG ": heredoc: open");
		return (fd);
	}
	return (heredoc_tmpfile(input, idx));
}
