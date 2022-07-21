/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce_c.c                                      :+:      :+:    :+:   */
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

static t_ast_a	*ast_a_join(t_ast_a *head, t_ast_a *tail)
{
	t_ast_a	*middle;

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

static t_ast_d	*ast_a_to_d(t_ast_a *a)
{
	t_ast_d	*d;
	char	*red_symbol;

	d = ft_x_malloc(sizeof(t_ast_d), PARSER_ERRMSG);
	if (a->red == NULL)
		return (NULL);
	red_symbol = a->red;
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
	d->num = a->red;
	d->word = a->word;
	d->next = NULL;
	free(a);
	return (d);
}

/* C     : C A               (9 */
void	lr_parse_reduce_9(t_lr_stack *stack)
{
	t_ast_c	*c;
	t_ast_a	*a;

	a = lr_stack_pop(stack);
	c = lr_stack_pop(stack);
	\
	if (a->red == NULL)
		c->a = ast_a_join(c->a, a);
	else
		c->d = ast_d_join(c->d, ast_a_to_d(a));
	\
	lr_stack_push(stack, \
		LR_N_C, lr_goto(LR_N_C, lr_stack_peak(stack)->state), c);
}

/* C     |   A               (10 */
void	lr_parse_reduce_10(t_lr_stack *stack)
{
	t_ast_c	*c;
	t_ast_a	*a;

	a = lr_stack_pop(stack);
	\
	c = ft_x_malloc(sizeof(t_ast_c), PARSER_ERRMSG);
	c->a = NULL;
	c->d = NULL;
	if (a->red == NULL)
		c->a = a;
	else
		c->d = ast_a_to_d(a);
	\
	lr_stack_push(stack, \
		LR_N_C, lr_goto(LR_N_C, lr_stack_peak(stack)->state), c);
}
