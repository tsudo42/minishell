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

void	exec_error(const char *name);

int		exec_l(t_ast_l *l);
int		exec_p(t_ast_p *p);
int		exec_s(t_ast_s *s);
int		exec_c(t_ast_c *c);
char	**exec_a(t_ast_a *a);
int		exec_d(t_ast_d	*d);

void	exec_stdfd_set(int *stdfds);
void	exec_stdfd_reset(int *stdfds);

#endif /* EXEC_INTERNAL_H */
