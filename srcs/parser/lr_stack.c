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

t_lr_stack	*lr_stack_init(void)
{
	t_lr_stack	*stack;

	stack = x_malloc(sizeof(t_lr_stack));
	stack->size = 0;
	stack->alloc_size = 16;
	stack->c = x_malloc(sizeof(t_lr_pair) * stack->alloc_size);
	return (stack);
}

void	lr_stack_push(t_lr_stack *stack, t_lr_token_type type, int state)
{
	t_lr_pair	*new_pair;

	if (stack->size == stack->alloc_size)
	{
		stack->alloc_size *= 2;
		new_pair = x_malloc(sizeof(t_lr_pair) * stack->alloc_size);
		ft_memmove(new_pair, stack->c, sizeof(t_lr_pair) * stack->size);
		free(stack->c);
		stack->c = new_pair;
	}
	stack->c[stack->size].type = type;
	stack->c[stack->size].state = state;
	stack->size++;
}

int	lr_stack_pop(t_lr_stack *stack, size_t popcount)
{
	if (stack->size < popcount)
		return (1);
	stack->size -= popcount;
	return (0);
}

t_lr_pair	*lr_stack_peak(t_lr_stack *stack)
{
	if (stack->size == 0)
		return (NULL);
	return (&(stack->c[stack->size - 1]));
}

void	lr_stack_terminate(t_lr_stack **stack_ptr)
{
	t_lr_stack	*stack;

	stack = *stack_ptr;
	if (stack != NULL)
		free(stack->c);
	free(stack);
	*stack_ptr = NULL;
}
