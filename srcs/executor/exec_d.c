/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/08/31 15:44:07 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "libft.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	exec_d_redirection(const char *word, int fd, t_ast_d_type type)
{
	int	open_fd;

	open_fd = -1;
	if (type == AST_D_REDIN)
		open_fd = open(word, O_RDONLY);
	else if (type == AST_D_REDOUT)
		open_fd = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == AST_D_REDAPP)
		open_fd = open(word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exec_error("undefined d type");
	if (open_fd < 0)
	{
		ft_dprintf(STDERR_FILENO, \
			"%s: %s: %s\n", EXEC_ERRMSG, word, strerror(errno));
		return (-1);
	}
	if (dup2(open_fd, fd) < 0)
	{
		perror(EXEC_ERRMSG ": dup2");
		return (-1);
	}
	close(open_fd);
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
		*is_err = 1;
		ft_putstr_fd(EXEC_ERRMSG ": ", STDERR_FILENO);
		errno = EBADF;
		if (fd < 0 || INT_MAX < fd)
			perror("file descriptor out of range");
		else
			perror(num);
		return (-1);
	}
	return (fd);
}

int	exec_d(t_ast_d *d, t_environ *env)
{
	int		is_err;
	long	fd;

	(void)env;
	is_err = 0;
	while (d != NULL && is_err == 0)
	{
		fd = calc_fd(d->type, d->num, &is_err);
		if (fd < 0)
			return (1);
		if (d->type != AST_D_HEREDOC)
			is_err = exec_d_redirection(d->word, fd, d->type);
		else
			is_err = exec_d_heredoc(d->heredoc_fd, fd);
		d = d->next;
	}
	return (is_err);
}
