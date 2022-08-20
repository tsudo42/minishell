/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "exec.h"

# include "utils.h"
# include "libft.h"

typedef struct s_pipe_info {
	pid_t	pid;
	int		fd_in;
	int		fd_out;
}	t_pipe_info;

typedef struct s_redir_list {
	int					to_fd;
	int					from_fd;
	struct s_redir_list	*next;
}	t_redir_list;

void	exec_error(const char *name);
int		exec_calc_retval(int stat);

int		exec_l(t_ast_l *l);
int		exec_p(t_ast_p *p);
int		exec_p_piped(t_ast_p *p, size_t p_len);
int		exec_s(t_ast_s *s);
int		exec_c(t_ast_c *c);
char	**exec_a(t_ast_a *a);
int		exec_d(t_ast_d	*d);

int		exec_d_redin(const char *word);
int		exec_d_redout(const char *word, int is_append);
int		exec_d_heredoc(const char *word);

void	exec_stdfd_set(int *stdfds);
void	exec_stdfd_reset(int *stdfds);

#endif /* EXEC_INTERNAL_H */
