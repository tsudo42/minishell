/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_p.c                                      :+:      :+:    :+:   */
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

static t_ast_p	*ast_p_join(t_ast_p *head, t_ast_p *tail)
{
	t_ast_p	*middle;

	if (head == NULL)
		return (tail);
	middle = head;
	while (middle->next != NULL)
		middle = middle->next;
	middle->next = tail;
	return (head);
}

/* P     : P PIPE S          (3 */
void	lr_parse_reduce_3(t_lr_stack *stack)
{
	t_ast_p	*p;
	t_ast_p	*prev_p;

	p = ft_x_malloc(sizeof(t_ast_p), PARSER_ERRMSG);
	\
	p->s = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	prev_p = lr_stack_pop(stack);
	\
	p->type = AST_P_S;
	p->c = NULL;
	p->next = NULL;
	prev_p = ast_p_join(prev_p, p);
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), prev_p);
}

/* P     | P PIPE C          (4 */
void	lr_parse_reduce_4(t_lr_stack *stack)
{
	t_ast_p	*p;
	t_ast_p	*prev_p;

	p = ft_x_malloc(sizeof(t_ast_p), PARSER_ERRMSG);
	\
	p->c = lr_stack_pop(stack);
	free(lr_stack_pop(stack));
	prev_p = lr_stack_pop(stack);
	\
	p->type = AST_P_C;
	p->s = NULL;
	p->next = NULL;
	prev_p = ast_p_join(prev_p, p);
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), prev_p);
}

/* P     |        S          (5 */
void	lr_parse_reduce_5(t_lr_stack *stack)
{
	t_ast_p	*p;

	p = ft_x_malloc(sizeof(t_ast_p), PARSER_ERRMSG);
	\
	p->s = lr_stack_pop(stack);
	\
	p->type = AST_P_S;
	p->c = NULL;
	p->next = NULL;
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), p);
}

/* P     |        C          (6 */
void	lr_parse_reduce_6(t_lr_stack *stack)
{
	t_ast_p	*p;

	p = ft_x_malloc(sizeof(t_ast_p), PARSER_ERRMSG);
	\
	p->c = lr_stack_pop(stack);
	\
	p->type = AST_P_C;
	p->s = NULL;
	p->next = NULL;
	\
	lr_stack_push(stack, \
		LR_N_P, lr_goto(LR_N_P, lr_stack_peak(stack)->state), p);
}
