/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_ad.c                                     :+:      :+:    :+:   */
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

static t_ast_d	*ast_d_join(t_ast_d *head, t_ast_d *tail)
{
	t_ast_d	*middle;

	if (head == NULL)
		return (tail);
	if (tail == NULL)
		return (head);
	middle = head;
	while (middle->next != NULL)
		middle = middle->next;
	middle->next = tail;
	return (head);
}

/* A     : RED WORD          (11 */
void	lr_parse_reduce_11(t_lr_stack *stack)
{
	t_ast_a	*a;

	a = ft_x_malloc(sizeof(t_ast_a), PARSER_ERRMSG);
	\
	a->word = lr_stack_pop(stack);
	a->red = lr_stack_pop(stack);
	\
	a->next = NULL;
	\
	lr_stack_push(stack, \
		LR_N_A, lr_goto(LR_N_A, lr_stack_peak(stack)->state), a);
}

/* A     |     WORD          (12 */
void	lr_parse_reduce_12(t_lr_stack *stack)
{
	t_ast_a	*a;

	a = ft_x_malloc(sizeof(t_ast_a), PARSER_ERRMSG);
	\
	a->word = lr_stack_pop(stack);
	\
	a->red = NULL;
	a->next = NULL;
	\
	lr_stack_push(stack, \
		LR_N_A, lr_goto(LR_N_A, lr_stack_peak(stack)->state), a);
}

/* D     : D RED WORD        (13 */
void	lr_parse_reduce_13(t_lr_stack *stack)
{
	t_ast_d	*new_d;
	char	*red_symbol;
	t_ast_d	*prev_d;

	new_d = ft_x_malloc(sizeof(t_ast_d), PARSER_ERRMSG);
	new_d->word = lr_stack_pop(stack);
	new_d->num = lr_stack_pop(stack);
	prev_d = lr_stack_pop(stack);
	\
	red_symbol = new_d->num;
	while (ft_isdigit(*red_symbol))
		red_symbol++;
	if (ft_strncmp("<", red_symbol, sizeof("<")) == 0)
		new_d->type = AST_D_REDIN;
	else if (ft_strncmp(">", red_symbol, sizeof(">")) == 0)
		new_d->type = AST_D_REDOUT;
	else if (ft_strncmp(">>", red_symbol, sizeof(">>")) == 0)
		new_d->type = AST_D_REDAPP;
	else
		new_d->type = AST_D_HEREDOC;
	*red_symbol = '\0';
	new_d->next = NULL;
	prev_d = ast_d_join(prev_d, new_d);
	lr_stack_push(stack, \
		LR_N_D, lr_goto(LR_N_D, lr_stack_peak(stack)->state), prev_d);
}

/* D     |   RED WORD        (14 */
void	lr_parse_reduce_14(t_lr_stack *stack)
{
	t_ast_d	*d;
	char	*red_symbol;

	d = ft_x_malloc(sizeof(t_ast_d), PARSER_ERRMSG);
	\
	d->word = lr_stack_pop(stack);
	d->num = lr_stack_pop(stack);
	\
	red_symbol = d->num;
	while (ft_isdigit(*red_symbol))
		red_symbol++;
	if (ft_strncmp("<", red_symbol, sizeof("<")) == 0)
		d->type = AST_D_REDIN;
	else if (ft_strncmp(">", red_symbol, sizeof(">")) == 0)
		d->type = AST_D_REDOUT;
	else if (ft_strncmp(">>", red_symbol, sizeof(">>")) == 0)
		d->type = AST_D_REDAPP;
	else
		d->type = AST_D_HEREDOC;
	*red_symbol = '\0';
	d->next = NULL;
	\
	lr_stack_push(stack, \
		LR_N_D, lr_goto(LR_N_D, lr_stack_peak(stack)->state), d);
}
