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

static int	clear_redir_list(t_redir_list *list)
{
	t_redir_list	*node;

	while (list != NULL)
	{
		node = list;
		list = node->next;
		close(node->from_fd);
		free(node);
	}
	return (1);
}

static int	join_redir_list(t_redir_list **list_ptr, int to_fd, int from_fd)
{
	t_redir_list	*node;

	node = malloc(sizeof(t_redir_list));
	if (node == NULL)
	{
		perror(EXEC_ERRMSG ": malloc");
		clear_redir_list(*list_ptr);
		*list_ptr = NULL;
		return (-1);
	}
	node->to_fd = to_fd;
	node->from_fd = from_fd;
	node->next = NULL;
	if (*list_ptr == NULL)
	{
		*list_ptr = node;
		return (0);
	}
	while ((*list_ptr)->next != NULL)
		(*list_ptr) = (*list_ptr)->next;
	(*list_ptr)->next = node;
	return (0);
}

static int	apply_redir_list(t_redir_list *list)
{
	t_redir_list	*node;

	while (list != NULL)
	{
		node = list;
		ft_x_dup2(node->from_fd, node->to_fd, EXEC_ERRMSG);
		close(node->from_fd);
		list = node->next;
		free(node);
	}
	return (0);
}

static int	calc_fd(t_ast_d_type type, char *num)
{
	long	fd;

	if (num == NULL || *num == '\0')
	{
		if (type == AST_D_REDIN)
			return (0);
		return (1);
	}
	fd = ft_strtol(num, NULL, 10);
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
	{
		errno = EBADF;
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
	t_redir_list	*redir_list;
	int				to_fd;
	int				from_fd;

	redir_list = NULL;
	while (d != NULL)
	{
		to_fd = calc_fd(d->type, d->num);
		if (to_fd < 0)
			return (clear_redir_list(redir_list));
		if (d->type == AST_D_REDIN)
			from_fd = exec_d_redin(d->word);
		else if (d->type == AST_D_REDOUT)
			from_fd = exec_d_redout(d->word, 0);
		else if (d->type == AST_D_REDAPP)
			from_fd = exec_d_redout(d->word, 1);
		else
			from_fd = exec_d_heredoc(d->word);
		if (from_fd < 0 || join_redir_list(&redir_list, to_fd, from_fd) < 0)
			return (clear_redir_list(redir_list));
		d = d->next;
	}
	return (apply_redir_list(redir_list));
}
