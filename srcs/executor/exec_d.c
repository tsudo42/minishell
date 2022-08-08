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

static int	exec_d_redin(const char *word, int fd)
{
	int open_fd;

//	if (0)
//	{
//		perror(word);
//		return (1);
//	}
	open_fd = open(word, O_RDONLY);
	(void)open_fd;
	(void)fd;
	return (0);
}

static int	exec_d_redout(const char *word, int fd, int is_append)
{
//	int open_fd;
	
//	(void)fd;
//	(void)open_fd;
	if (is_append == 0)
	{
//		open_fd = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_putendl_fd(word, fd);
		//		ft_putendl_fd(word, open_fd);
//		close(open_fd);
	}
	else if (is_append == 1)
	{
//		open_fd = open(word, O_WRONLY | O_CREAT | O_APPEND, 0644);
//		ft_putendl_fd(word, open_fd);
		ft_putendl_fd(word, fd);
		//		close(open_fd);
	}
	else
		return (-1);
	return (0);
}

static int	exec_d_heredoc(const char *word, int fd)
{
	heredoc(word, fd);
	return (0);
}

int	exec_d(t_ast_d *d)
{
	int		is_err;
	long	fd;

	is_err = 0;
	while (d != NULL && is_err)
	{
		fd = ft_strtol(d->num, NULL, 10);
		if (fd > 3)
		{
			perror("minishell: file descriptor out of range");
			return (1);
		}
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
	return (is_err);
}
