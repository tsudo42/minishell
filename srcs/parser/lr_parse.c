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
	lr_stack_push(stack, (*tokens)->type, param);
	*tokens = (*tokens)->next;
	return (0);
}

static int	lr_parse_reduce(t_token_list **tokens, t_lr_stack *stack, int param)
{
	(void)tokens;
	lr_stack_pop(stack, lr_get_size_of_rule(param));
	lr_stack_push(stack, lr_get_left_of_rule(param), \
	lr_goto(lr_get_left_of_rule(param), lr_stack_peak(stack)->state));
	lr_apply_rule(param);
	return (0);
}

static int	lr_parse_loop(t_token_list **tokens, t_lr_stack *stack)
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
	if (action == LR_ACT_ACCEPT)
		return (0);
	return (lr_parse_error(*tokens));
}

int	lr_parse(t_token_list *token_list)
{
	t_lr_stack	*stack;
	int			ret_val;

	stack = lr_stack_init();
	lr_stack_push(stack, LR_NULL, 0);
	ret_val = lr_parse_loop(&token_list, stack);
	lr_stack_terminate(&stack);
	return (ret_val);
}
