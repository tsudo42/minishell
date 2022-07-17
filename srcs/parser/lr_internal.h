/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LR_INTERNAL_H
# define LR_INTERNAL_H

# include "lr_func.h"
# include "utils.h"
# include <stdlib.h>

typedef struct s_lr_pair {
	t_lr_token_type	type;
	int				state;
}	t_lr_pair;

typedef struct s_lr_stack {
	size_t		size;
	size_t		alloc_size;
	t_lr_pair	*c;
}	t_lr_stack;

/* lr_stack.c */
t_lr_stack		*lr_stack_init(void);
void			lr_stack_push(t_lr_stack *stack, \
	t_lr_token_type type, int state);
int				lr_stack_pop(t_lr_stack *stack, size_t popcount);
t_lr_pair		*lr_stack_peak(t_lr_stack *stack);
void			lr_stack_terminate(t_lr_stack **stack_ptr);

/* NOTIMPLEMENTED */
t_lr_token_type	lr_iter(t_token_list **tokens);
t_lr_token_type	lr_peak(t_token_list **tokens);

#endif /* LR_INTERNAL_H */
