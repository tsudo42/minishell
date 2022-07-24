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
#include <stdlib.h>
#include <stdio.h>

/* NOTIMPLEMENTED */
static int	exec_d_redin(const char *word, int fd)
{
	if (0)
	{
		perror(word);
		return (1);
	}
	(void)word;
	(void)fd;
	return (0);
}

/* NOTIMPLEMENTED */
static int	exec_d_redout(const char *word, int fd, int is_append)
{
	(void)word;
	(void)fd;
	(void)is_append;
	return (0);
}

/* NOTIMPLEMENTED */
static int	exec_d_heredoc(const char *word, int fd)
{
	(void)word;
	(void)fd;
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
