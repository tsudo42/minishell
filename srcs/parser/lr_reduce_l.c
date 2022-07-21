/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_internal.h"
#include "exec.h"
#include "libft.h"

/**
L     : L OP P            (1
      |      P            (2
      ;
P     : P PIPE S          (3
      | P PIPE C          (4
      |        S          (5
      |        C          (6
      ;
S     : LBRACE L RBRACE D (7
      | LBRACE L RBRACE   (8
      ;
C     : C A               (9
      |   A               (10
      ;
A     : RED WORD          (11
      |     WORD          (12
      ;
D     : D RED WORD        (13
      |   RED WORD        (14
      ;
*/

static t_ast_l	*ast_l_join(t_ast_l *head, t_ast_l *tail)
{
	t_ast_l	*middle;

	if (head == NULL)
		return (tail);
	middle = head;
	while (middle->next != NULL)
		middle = middle->next;
	middle->next = tail;
	return (head);
}

/* L     : L OP P            (1 */
void	lr_parse_reduce_1(t_lr_stack *stack)
{
	t_ast_l	*l;
	char	*op;
	t_ast_l	*prev_l;

	l = ft_x_malloc(sizeof(t_ast_l), PARSER_ERRMSG);
	\
	l->p = lr_stack_pop(stack);
	op = lr_stack_pop(stack);
	prev_l = lr_stack_pop(stack);
	\
	if (ft_strncmp("&&", op, sizeof("&&")) == 0)
		l->op = AST_L_AND;
	else
		l->op = AST_L_OR;
	free(op);
	l->next = NULL;
	prev_l = ast_l_join(prev_l, l);
	\
	lr_stack_push(stack, \
		LR_N_L, lr_goto(LR_N_L, lr_stack_peak(stack)->state), prev_l);
}

/* L      |      P            (2 */
void	lr_parse_reduce_2(t_lr_stack *stack)
{
	t_ast_l	*l;

	l = ft_x_malloc(sizeof(t_ast_l), PARSER_ERRMSG);
	\
	l->p = lr_stack_pop(stack);
	\
	l->op = AST_L_AND;
	l->next = NULL;
	\
	lr_stack_push(stack, \
		LR_N_L, lr_goto(LR_N_L, lr_stack_peak(stack)->state), l);
}
