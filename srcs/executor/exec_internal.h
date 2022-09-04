/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/09/04 09:05:37 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "exec.h"

# define EXEC_ERRMSG "minishell"
# define EXEC_INTERNAL_ERRMSG "exec internal error"
# define EXEC_INTERNAL_ERRNUM -1

typedef struct s_pipe_info {
	pid_t	pid;
	int		fd_in;
	int		fd_out;
}	t_pipe_info;

void	exec_error(const char *name);
void	ready_exec_signal(void);
int		exec_calc_retval(int stat);

int		ready_heredoc_signal(int *is_error);
void	cleanup_heredoc_signal(int *is_error);

char	*heredoc_input(char *delim, int *is_error);
int		heredoc_set(char *delim, int *idx);
int		heredoc_ready(t_ast *ast);

int		exec_l(t_ast_l *l);
int		exec_p(t_ast_p *p);
int		exec_p_piped(t_ast_p *p, size_t p_len);
int		exec_s(t_ast_s *s);
int		exec_c(t_ast_c *c);
char	**exec_a(t_ast_a *a);
int		exec_d(t_ast_d	*d);

void	exec_stdfd_set(int *stdfds);
void	exec_stdfd_reset(int *stdfds);

#endif /* EXEC_INTERNAL_H */
