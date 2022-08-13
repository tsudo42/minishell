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
	int len;
	char	buf[BUFSIZE]; // should I avoid this and use malloc instead?

	open_fd = open(word, O_RDONLY);
	while ((len = read(open_fd, buf, BUFSIZE)) > 0)
		write(fd, buf, len);
	close(open_fd);
	if (len < 0)
	{
		perror("exec_d_redin");
		return (0);
	}
	exit (0);
	//	return (0);
}

static int	exec_d_redout(const char *word, int fd, int is_append)
{
	int open_fd;
	int len;
	char	buf[BUFSIZE]; // should I avoid this and use malloc instead?
	int option;

	(void)fd;
	printf("word:%s\n", word);
	printf("fd:%d\n", fd);
	printf("options:%d, %d\n", O_TRUNC, O_APPEND);
	len = 1;
	if (is_append == 0 || is_append == 1)
	{
		if (is_append == 0)
			option = O_TRUNC;
		else
			option = O_APPEND;
		//		open_fd = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		open_fd = open(word, O_WRONLY | O_CREAT | option, 0644);
		while ((len = read(fd, buf, BUFSIZE)) > 0) 
			write(open_fd, buf, len);
		close(open_fd);
	}
	/*	else if (is_append == 1)
			{
			open_fd = open(word, O_WRONLY | O_CREAT | O_APPEND, 0644);
			while ((len = read(open_fd, buf, BUFSIZE)) > 0) 
			write(fd, buf, len);
			close(open_fd);
			}
			*/
	else
		return (0);
	if (len < 0)
	{
		perror("exec_d_redout");
		return (0);
	}
	exit (0);
}

static long	calc_fd(t_ast_d_type type, char *num, int *is_err)
{
	long	fd;

	if (num == NULL || *num == '\0')
	{
		if (type == AST_D_REDIN)
			return (0);
		return (1);
	}
	fd = ft_strtol(num, NULL, 10);
	if (fd < 0 || INT_MAX < fd)
	{
		errno = EBADF;
		*is_err = 1;
		perror("minishell: file descriptor out of range");
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
//		printf("fd: %ld\n", fd);
//		printf("d->type: %d\n", d->type);
//		printf("d->num: %d\n", d->type);
		if (d->type == AST_D_REDIN)
			is_err = exec_d_redin(d->word, fd);
		else if (d->type == AST_D_REDOUT)
			is_err = exec_d_redout(d->word, fd, 0);
		else if (d->type == AST_D_REDAPP)
			is_err = exec_d_redout(d->word, fd, 1);
		else if (d->type == AST_D_HEREDOC)
			is_err = exec_d_heredoc(d->word, fd);
		else
			exec_error("undefined d type");
		d = d->next;
	}
//	printf("parent\n");
	return (is_err);
}
