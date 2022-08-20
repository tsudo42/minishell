/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_d_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

#define MINISHELL_HEREDOC_FILENO 3

int	exec_d_redin(const char *word)
{
	int	fd;

	(void)word;
	(void)fd;
	return (0);
}

int	exec_d_redout(const char *word, int is_append)
{
	int	fd;

	(void)word;
	(void)is_append;
	(void)fd;
	return (0);
}

int	exec_d_heredoc(const char *word)
{
	int	tmp_fd;

	(void)word;
	tmp_fd = ft_x_dup(STDERR_FILENO, EXEC_ERRMSG ": dup");
	ft_x_dup2(MINISHELL_HEREDOC_FILENO, STDERR_FILENO, EXEC_ERRMSG ": dup2");
	write(STDERR_FILENO, "heredoc > \n", 11);
	ft_x_dup2(tmp_fd, STDERR_FILENO, EXEC_ERRMSG ": dup2");
	close(tmp_fd);
	return (0);
}
