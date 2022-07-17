/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_rule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:23:08 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:55:19 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "lr_func.h"

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

int	lr_get_size_of_rule(int rule)
{
	static const int	size_table[15] = {\
		-1,
		3, 1,
		3, 3, 1, 1,
		4, 3,
		2, 1,
		2, 1,
		3, 2
	};

	if (rule <= 0 || rule >= 15)
		return (-1);
	return (size_table[rule]);
}

t_lr_token_type	lr_get_left_of_rule(int rule)
{
	static const t_lr_token_type	left_table[15] = {\
		LR_NULL,
		LR_N_L, LR_N_L,
		LR_N_P, LR_N_P, LR_N_P, LR_N_P,
		LR_N_S, LR_N_S,
		LR_N_C, LR_N_C,
		LR_N_A, LR_N_A,
		LR_N_D, LR_N_D
	};

	if (rule <= 0 || rule >= 15)
		return (-1);
	return (left_table[rule]);
}
