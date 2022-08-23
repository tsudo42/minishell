/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "libft.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 2048

static int	exec_d_redin(const char *word, int fd)
{
	int open_fd;

	open_fd = open(word, O_RDONLY);
	if (open_fd < 0)
	{
		perror(EXEC_ERRMSG ": open_fd");
		return (-1);
	}
	return (ft_r_dup2(open_fd, fd, EXEC_ERRMSG));
}

static int	exec_d_redout(const char *word, int fd, int is_append)
{
	int open_fd;
	int ret;

	if (is_append == 0)
		open_fd = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		open_fd = open(word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (open_fd < 0)
	{
		perror(EXEC_ERRMSG ": open_fd");
		return (-1);
	}
	ret = ft_r_dup2(open_fd, fd, EXEC_ERRMSG);
	close(open_fd);
	exec_d_redin(word, 0);
	if (ret < 0)
		return (-1);
	return (0);
}

static int	exec_d_heredoc(int from_fd, int to_fd)
{
	int	fd;

	fd = dup2(from_fd, to_fd);
	if (fd < 0)
		perror(EXEC_ERRMSG ": dup2");
	close(from_fd);
	if (fd < 0)
		return (-1);
	return (0);
}

static long	calc_fd(t_ast_d_type type, char *num, int *is_err)
{
	long	fd;

	if (num == NULL || *num == '\0')
	{
		if (type == AST_D_REDIN || type == AST_D_HEREDOC)
			return (0);
		return (1);
	}
	fd = ft_strtol(num, NULL, 10);
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
	{
		errno = EBADF;
		*is_err = 1;
		ft_putstr_fd(EXEC_ERRMSG ": ", STDERR_FILENO);
		if (fd < 0 || INT_MAX < fd)
			perror("file descriptor out of range");
		else
			perror(num);
		return (-1);
	}
	return (fd);
}

int	exec_d(t_ast_d *d)
{
	int		is_err;
	long	fd;

	is_err = 0;
	while (d != NULL && is_err == 0)
	{
		fd = calc_fd(d->type, d->num, &is_err);
		if (fd < 0)
			return (1);
		if (d->type == AST_D_REDIN)
			is_err = exec_d_redin(d->word, fd);
		else if (d->type == AST_D_REDOUT)
			is_err = exec_d_redout(d->word, fd, 0);
		else if (d->type == AST_D_REDAPP)
			is_err = exec_d_redout(d->word, fd, 1);
		else if (d->type == AST_D_HEREDOC)
			is_err = exec_d_heredoc(d->heredoc_fd, fd);
//			is_err = exec_d_heredoc(d->word, fd);
		else
			exec_error("undefined d type");
		d = d->next;
	}
	return (is_err);
}
