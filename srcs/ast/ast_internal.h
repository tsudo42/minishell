/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_INTERNAL_H
# define AST_INTERNAL_H

# include "ast.h"

t_ast_a	*ast_join_a(t_ast_a *a_head, t_ast_a *a_tail);
t_ast_d	*ast_join_d(t_ast_d *d_head, t_ast_d *d_tail);

# define PRINT_BUFSIZE 42

void	print_ast_l(char pref[PRINT_BUFSIZE], t_ast_l *l);
void	print_ast_p(char pref[PRINT_BUFSIZE], t_ast_p *p);
void	print_ast_s(char pref[PRINT_BUFSIZE], t_ast_s *s);
void	print_ast_c(char pref[PRINT_BUFSIZE], t_ast_c *c);
void	print_ast_a(char pref[PRINT_BUFSIZE], t_ast_a *a);
void	print_ast_d(char pref[PRINT_BUFSIZE], t_ast_d *d);

#endif /* AST_INTERNAL_H */
