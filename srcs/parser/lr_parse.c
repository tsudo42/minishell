/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_internal.h"

static int	lr_parse_shift(t_token_list **tokens, t_lr_stack *stack, int param)
{
	lr_stack_push(stack, (*tokens)->type, param, (*tokens)->str);
	(*tokens)->str = NULL;
	*tokens = (*tokens)->next;
	return (0);
}

static int	lr_parse_reduce(t_token_list **tokens, t_lr_stack *stack, int param)
{
	static void	(*reduce_funcs[15])(t_lr_stack*) = {
		NULL, lr_parse_reduce_1, lr_parse_reduce_2, lr_parse_reduce_3,
		lr_parse_reduce_4, lr_parse_reduce_5, lr_parse_reduce_6,
		lr_parse_reduce_7, lr_parse_reduce_8, lr_parse_reduce_9,
		lr_parse_reduce_10, lr_parse_reduce_11, lr_parse_reduce_12,
		lr_parse_reduce_13, lr_parse_reduce_14
	};

	(void)tokens;
	if (param <= 0 || 15 <= param)
		return (1);
	reduce_funcs[param](stack);
	return (0);
}

static t_ast	*lr_parse_loop(t_token_list **tokens, t_lr_stack *stack)
{
	t_lr_action_type	action;
	int					param;

	while (1)
	{
		action = lr_action((*tokens)->type, lr_stack_peak(stack)->state);
		param = lr_action_param((*tokens)->type, lr_stack_peak(stack)->state);
		if (action == LR_ACT_SHIFT)
			lr_parse_shift(tokens, stack, param);
		else if (action == LR_ACT_REDUCE)
			lr_parse_reduce(tokens, stack, param);
		else
			break ;
	}
	if (action != LR_ACT_ACCEPT)
	{
		lr_parse_error(*tokens);
		return (NULL);
	}
	return (lr_stack_pop(stack));
}

t_ast	*lr_parse(t_token_list *token_list)
{
	t_lr_stack	*stack;
	t_ast		*ast_root;

	stack = lr_stack_init();
	lr_stack_push(stack, LR_NULL, 0, NULL);
	ast_root = lr_parse_loop(&token_list, stack);
	lr_stack_terminate(&stack);
	return (ast_root);
}
