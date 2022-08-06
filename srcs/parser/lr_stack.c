/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_internal.h"
#include "libft.h"

t_lr_stack	*lr_stack_init(void)
{
	t_lr_stack	*stack;

	stack = ft_x_malloc(sizeof(t_lr_stack), PARSER_ERRMSG);
	stack->size = 0;
	stack->alloc_size = 16;
	stack->c = \
		ft_x_malloc(sizeof(t_lr_node) * stack->alloc_size, PARSER_ERRMSG);
	return (stack);
}

void	lr_stack_push(t_lr_stack *stack, \
	t_lr_token_type type, int state, void *content)
{
	t_lr_node	*new_stack_c;

	if (stack->size == stack->alloc_size)
	{
		stack->alloc_size *= 2;
		new_stack_c = \
			ft_x_malloc(sizeof(t_lr_node) * stack->alloc_size, PARSER_ERRMSG);
		ft_memmove(new_stack_c, stack->c, sizeof(t_lr_node) * stack->size);
		free(stack->c);
		stack->c = new_stack_c;
	}
	stack->c[stack->size].type = type;
	stack->c[stack->size].state = state;
	stack->c[stack->size].content = content;
	stack->size++;
}

void	*lr_stack_pop(t_lr_stack *stack)
{
	if (stack->size == 0)
		return (NULL);
	stack->size--;
	return (stack->c[stack->size].content);
}

t_lr_node	*lr_stack_peak(t_lr_stack *stack)
{
	if (stack->size == 0)
		return (NULL);
	return (&(stack->c[stack->size - 1]));
}

void	lr_stack_terminate(t_lr_stack **stack_ptr)
{
	t_lr_stack	*stack;

	stack = *stack_ptr;
	if (stack == NULL)
		return ;
	while (stack->size-- > 0)
	{
		if (stack->c[stack->size].type == LR_N_L)
			ast_free_l(stack->c[stack->size].content);
		else if (stack->c[stack->size].type == LR_N_P)
			ast_free_p(stack->c[stack->size].content);
		else if (stack->c[stack->size].type == LR_N_S)
			ast_free_s(stack->c[stack->size].content);
		else if (stack->c[stack->size].type == LR_N_C)
			ast_free_c(stack->c[stack->size].content);
		else if (stack->c[stack->size].type == LR_N_A)
			ast_free_a(stack->c[stack->size].content);
		else if (stack->c[stack->size].type == LR_N_D)
			ast_free_d(stack->c[stack->size].content);
		else
			free(stack->c[stack->size].content);
	}
	free(stack->c);
	free(stack);
	*stack_ptr = NULL;
}
